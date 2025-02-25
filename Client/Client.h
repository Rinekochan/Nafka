#pragma once

#ifdef WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#define close closesocket
#else
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#define SOCKET int
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#endif

namespace Nafka {
    struct Client {
        Client();
        Client& accept_c(const SOCKET& server);
        void close_c() const;
    private:
        SOCKET m_socket;
        sockaddr_in m_address;
        socklen_t m_address_len;
    };
}
