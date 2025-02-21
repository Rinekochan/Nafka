﻿#include "Client.h"
#include "../Logger/Logger.h"
#include <iostream>

using namespace Nafka;

Client::Client() : m_socket(), m_address(), m_address_len(sizeof(m_address)) {}


Client& Client::accept_c(const SOCKET server) {
    m_socket = accept(server, reinterpret_cast<struct sockaddr*>(&m_address), &m_address_len);
    Logger::print_current_time(std::cout);
    std::cout << "[Client]: Client connected\n";
    return *this;
}

void Client::close_c() const {
    close(m_socket);
}

