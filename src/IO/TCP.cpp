#include "IO/TCP.h"

#include <stdio.h>
#include <algorithm>
#include <unistd.h>

using namespace IO;

TCP_Interface::TCP_Interface()
{
	this->type = TYPE_TCP;
    this->serverInfo.listeningPort = 9010;
    init();
}

TCP_Interface::TCP_Interface(int listeningPort)
{
	this->type = TYPE_TCP;
    this->serverInfo.listeningPort = listeningPort;
    init();
}

TCP_Interface::~TCP_Interface()
{
    closeServer();
}

int TCP_Interface::readMessage(uint8_t* dest, const int num)
{
	return RX_BUFFER_PTR.get()->dequeue(dest, num);
}

int TCP_Interface::writeMessage(uint8_t* src, const int num)
{
	return TX_BUFFER_PTR.get()->enqueue(src, num);
}

void TCP_Interface::init()
{
	if (initBuffers() < 0)
		return;

	if (openServer() < 0) 
		return;

	thread_active = true;
    listenThreadObj = std::thread(&TCP_Interface::_listenerThread, this);
    dataThreadObj = std::thread(&TCP_Interface::_dataThread, this);
}

/**
 * @brief 	Opens a server to accept incoming client connections.
 * 
 * @return 	int	Returns -1 for failure and >= 0 for success
 */
int TCP_Interface::openServer()
{
    serverInfo.socketID = socket(AF_INET, SOCK_STREAM, 0);
	if (serverInfo.socketID < 0)
	{
		perror("socket");
		return -1;
	}

	serverInfo.server_addr.sin_family = AF_INET;
	serverInfo.server_addr.sin_port = htons(serverInfo.listeningPort);
	serverInfo.server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	int retVal = bind(serverInfo.socketID, (struct sockaddr*)&serverInfo.server_addr, sizeof(serverInfo.server_addr));
	if (retVal < 0)
	{
		//close();
		perror("Bind Error:");
		return -1;
	}

	printf("Server Listening for connections at port: %d\n", serverInfo.listeningPort);

	// Configures server port to listen for connections
	while (listen(serverInfo.socketID, 5) < 0)
	{
		perror("listen");
		return -1;
	}
    
    return 1;

}

/**
 * @brief 	Closes the server and all client connections
 * 
 */
void TCP_Interface::closeServer()
{

	for (auto &client : clientList)
	{
		shutdown(client.socketID, SHUT_RDWR);
	}

	shutdown(serverInfo.socketID, SHUT_RDWR);
	clientList.resize(0);
	thread_active = false;

}

void TCP_Interface::closeClient(int socketID)
{
	for(auto iter = clientList.begin(); iter != clientList.end();)
    {
        if(iter->socketID == socketID)
        {
            iter = clientList.erase(iter);
        } else {
            ++iter;
        }
    }
}

/**
 * @brief 	Writes data to the socket
 * 
 * @param socketID 	The socket to write to
 * @param data 		A pointer to the data to write
 * @param amount 	The amount of data to write
 * @return int 		The amount of data written or -1 for an error
 */
int TCP_Interface::writeToSocket(const int socketID, const char* data, const int amount)
{
	if (data == nullptr) 
		return -1;
	
	return send(socketID, data, amount, 0);
}

/**
 * @brief 	Read data from a socket
 * 
 * @param socketID 	The socket to read from
 * @param data 		A buffer to store the data in
 * @param amount 	The amount of data to read
 * @return int 		The actual amount of data read or -1 for an error
 */
int TCP_Interface::readFromSocket(const int socketID, char* data, const int amount)
{
	if (data == nullptr) 
		return -1;
	
	auto retVal = recv(socketID, data, amount, MSG_DONTWAIT);
	if(retVal < 0)
	{
		perror("Read");
		return -1;
	} 

	return retVal;
}

void TCP_Interface::_listenerThread()
{

	tcp::ClientInfo newClient;

	while(thread_active)
	{
		memset(&newClient, 0, sizeof(newClient));

		newClient.socketID = accept(serverInfo.socketID, (struct sockaddr*)&newClient.address, &newClient.address_length);
		if (newClient.socketID < 0)
		{
			perror("TCPClient Connection");
			closeServer();
			return;
		}

		getpeername(newClient.socketID, (struct sockaddr*)&newClient.address, &newClient.address_length);
		newClient.port = ntohs((&newClient.address)->sin_port);
		inet_ntop(AF_INET, &(newClient.address.sin_addr), newClient.ip_addr, sizeof(newClient.ip_addr));

		newClient.pollObject.fd = newClient.socketID;
		newClient.pollObject.events = POLLOUT | POLLIN | POLLERR;

		clientWriteLock.lock();
		clientList.push_back(newClient);
		clientWriteLock.unlock();

		usleep(10000);

	}

}

void TCP_Interface::_dataThread()
{

	uint8_t* data = new uint8_t[BUFFER_SIZE];

	while(thread_active)
	{

		if(TX_BUFFER_PTR.get()->getDataSize() > 0)
		{
			int dataSize = TX_BUFFER_PTR.get()->dequeue(data, TX_BUFFER_PTR.get()->getDataSize());
			for(tcp::ClientInfo& client : clientList)
			{
				_dataWrite(client, data, dataSize);
			}
		}

		if(clientWriteLock.try_lock())
		{
			for(tcp::ClientInfo& client : clientList)
			{
				// Poll for actions required
				if (poll(&(client.pollObject), 1, 0) < 0)
					perror("Poll");

				// Socket Error Occured
				if ((client.pollObject.revents & POLLERR))
				{
					client.pollObject.revents -= POLLERR;
					closeClient(client.socketID);
				}

				// Socket ready to read
				if(client.pollObject.revents & POLLIN)
				{
					client.pollObject.revents -= POLLIN;
					_dataRead(client, data);
				}

			}
			clientWriteLock.unlock();
		}

		usleep(500);

	}

	delete data;

}

void TCP_Interface::_dataRead(tcp::ClientInfo& client, uint8_t* dataBuffer)
{
	int dataRead = recv(client.socketID, (void*)dataBuffer, BUFFER_SIZE, MSG_DONTWAIT);

	if (dataRead <= 0) 
	{ 
		closeClient(client.socketID);
		return;
	}
	
	//printf("%s", dataBuffer);
	//TX_BUFFER_PTR.get()->enqueue(dataBuffer, dataRead);
	
	if(RX_BUFFER_PTR.get()->enqueue(dataBuffer, dataRead) != dataRead)
		return; // TODO: Implement Error handling

}

void TCP_Interface::_dataWrite(tcp::ClientInfo& client, uint8_t* dataBuffer, int size)
{
	writeToSocket(client.socketID, (const char*)dataBuffer, size);
}

