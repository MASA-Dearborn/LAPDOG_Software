#pragma once

#include <sys/socket.h>
#include <arpa/inet.h>
#include <poll.h>
#include <string.h>
#include <vector>
#include <thread>
#include <mutex>

#include "IOInterface.h"

namespace IO
{

    namespace tcp
    {

        struct ClientInfo
        {
            int socketID;
            int port;
            bool isConnected;
            char ip_addr[INET6_ADDRSTRLEN];
            struct sockaddr_in address;
            socklen_t address_length;
            struct pollfd pollObject;
        };

        struct ServerInfo
        {
            sockaddr_in server_addr;
            int listeningPort;
            int socketID;
        };

    };

    /**
     * @brief   TCP implementation fo IOInterface
     * 
     */
    class TCP_Interface : public IOInterface
    {
        public:
            TCP_Interface();
            TCP_Interface(int listeningPort);
            virtual ~TCP_Interface();

            // Inherited from IOInterface
            int readMessage(uint8_t* dest, const int num);
            int writeMessage(uint8_t* src, const int num);

        protected:

            void init();
            int openServer();
            void closeServer();
            void closeClient(int socketID);

            int writeToSocket(const int socketID, const char* data, const int amount);
            int readFromSocket(const int socketID, char* data, const int amount);

            void _listenerThread();
            void _dataThread();
            void _dataRead(tcp::ClientInfo& client, uint8_t* dataBuffer);
            void _dataWrite(tcp::ClientInfo& client, uint8_t* data, int size);

        private:

            std::thread listenThreadObj;
            std::thread dataThreadObj;
            std::mutex clientWriteLock;
            bool thread_active = false;

            tcp::ServerInfo serverInfo;
            std::vector<tcp::ClientInfo> clientList;

    };

    /**
     * @brief   Basic client implementation for testing purposes
     */
    class TCPClient
    {
        public:
            TCPClient() {}
            TCPClient(const char* ip, int port) { initClient(ip, port); }
            ~TCPClient() { disconnect(); }

            int write(char* src, int amount) { return send(client.socketID, src, amount, 0); }
            int read(char* dest, int amount) { return recv(client.socketID, dest, amount, MSG_DONTWAIT); };
            void disconnect() { shutdown(client.socketID, SHUT_RDWR); }

            void initClient(const char* ip, int port)
            {
                client.socketID = socket(AF_INET, SOCK_STREAM, 0);
                client.address.sin_family = AF_INET;
                client.address.sin_port = htons(port);
                client.address.sin_addr.s_addr = inet_addr(ip);
                connect(client.socketID, (struct sockaddr *)&client.address, sizeof(client.address));
            }

            tcp::ClientInfo client;
    };

}