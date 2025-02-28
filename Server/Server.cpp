#include "Server.h"
#include "../Logger/Logger.h"


using namespace Nafka;

Server::Server() : m_socket(), m_address() {
    #ifdef WIN32
        // Initialize WinSock
        WSAData wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            throw std::runtime_error("WSAStartup failed\n");
        }

        if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
            WSACleanup();
            throw std::runtime_error("Version 2.0+ of WinSock not available\n");
        }
    #endif
}


Server& Server::set_socket(const int address_family, const int socket_type, const int protocol) {
    m_socket = socket(address_family, socket_type, protocol);
    if (m_socket == INVALID_SOCKET) {
        throw std::system_error(errno, std::system_category());
    }
    return *this;
}
SOCKET& Server::get_socket() {
    return m_socket;
}

// Force the program to reuse the port if a connection is hanging
Server& Server::set_reusable(const int level, const int option_name, const char* option_val, const int option_len) {
    if (setsockopt(this->m_socket, level, option_name, option_val, option_len) == SOCKET_ERROR) {
        close_s();
        throw std::system_error(errno, std::system_category());
    }
    return *this;
}

Server& Server::set_server_ip(const short address_family, const u_long src_address_scope, const u_short port) {
    m_address.sin_family = address_family;
    m_address.sin_addr.s_addr = src_address_scope;
    m_address.sin_port = htons(port);
    return *this;
}

Server& Server::bind_s() {
    if (bind(m_socket, reinterpret_cast<sockaddr*>(&m_address), sizeof(m_address)) == SOCKET_ERROR) {
        close_s();
        throw std::system_error(errno, std::system_category());
    }
    return *this;
}

Server& Server::listen_s(const int connection_amt) {
    if (listen(m_socket, connection_amt) == SOCKET_ERROR) {
        close_s();
        throw std::system_error(errno, std::system_category());
    }
    Logger::print_current_time(std::cout);
    Logger::print_log(std::cout, "[Server]: Waiting for clients on port 9092...\n");
    return *this;
}

void Server::close_s() const {
    close(m_socket);
}
