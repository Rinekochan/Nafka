//
// Created by hoang on 28/02/2025.
//

#include "Connection.h"

#include "../../Logger/Logger.h"
#include "../Api/ApiFactory.h"
#include "../Request/Request.h"

using namespace Nafka::Connection;

void Connection::bind_client_socket(SOCKET&& socket) {
    client_socket = std::make_unique<SOCKET>(socket);
}

void Connection::handle_requests() const {
    const Request request(receive_data());

    Logger::print_log(std::format("Request:\n{}\n", request.to_string()));

    send_responses(request);
}

void Connection::send_responses(const Request& request) const {

    const Response response = ApiFactory::getApiResponseFunc(request.header.request_api_key)(request);

    try {
        send_data(response.serialize());
        Logger::print_current_time();
        Logger::print_log("[Server]: Send response: \n");
        Logger::print_log(std::format("Response:\n{}\n", response.to_string()));
    } catch (const std::exception& e) {
        Logger::print_current_time(std::cerr);
        Logger::print_log(std::format("[Server]: {}\n", e.what()));
    }
}

std::vector<uint8_t> Connection::receive_data() const {
    std::vector<uint8_t> data(1024);
    const ssize_t bytes_received = recv(*client_socket.get(), reinterpret_cast<char*>(data.data()), data.size(), 0);

    if (bytes_received < 0) {
        throw std::errc::network_down;
    }

    data.resize(bytes_received);

    Logger::print_current_time();

    std::string str_data = "";
    std::for_each(data.begin(), data.end(), [&str_data](const char c) { str_data += c; });

    Logger::print_log(std::format("[Server]: Receive request: \n"));

    return data;
}

void Connection::send_data(const std::vector<uint8_t>& data) const {
    if (const ssize_t bytes_sent = send(*client_socket.get(),
                                  reinterpret_cast<const char*>(data.data()),
                                  data.size(), 0);
        bytes_sent <= 0) {
        throw std::errc::network_unreachable;
    }
}
