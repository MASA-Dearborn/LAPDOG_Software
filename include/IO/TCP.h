#pragma once

#include <sys/socket.h>
#include <arpa/inet.h>
#include <poll.h>
#include <string.h>
#include <vector>
#include <thread>

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

    class TCP_Interface : public IOInterface
    {
        public:
            TCP_Interface();
            TCP_Interface(int listeningPort);
            ~TCP_Interface();

            // Inherited from IOInterface
            int readMessage(void* dest, const int num);
            int writeMessage(void* src, const int num);

        protected:

            void init();
            int openServer();
            void closeServer();

            int writeToSocket(const int socketID, const char* data, const int amount);
            int readFromSocket(const int socketID, char* data, const int amount);

            void _listenerThread();
            void _dataThread();
            void _dataRead(tcp::ClientInfo& client);
            void _dataWrite(tcp::ClientInfo& client, uint8_t* data, int size);

        private:

            std::thread listenThreadObj;
            std::thread dataThreadObj;
            bool thread_active = false;

            tcp::ServerInfo serverInfo;
            std::vector<tcp::ClientInfo> clientList;

    };

}