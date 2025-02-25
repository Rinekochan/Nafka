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
    struct Server {
        Server();
        Server& set_socket(int address_family, int socket_type, int protocol);
        SOCKET& get_socket();
        Server& set_reusable(int level, int option_name, const char* option_val, int option_len);
        Server& set_server_ip(short address_family, u_long src_address_scope, u_short port);
        Server& bind_s();
        Server& listen_s(int connection_amt);
        void close_s() const;
    private:
        SOCKET m_socket;
        sockaddr_in m_address;
    };
}
