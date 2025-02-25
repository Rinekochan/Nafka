#include <format>
#include <iostream>

#include "Client/Client.h"
#include "Logger/Logger.h"
#include "Server/Server.h"


int main(int argc, char* argv[]) {
    using std::cout, std::cerr, Nafka::Server, Nafka::Client;

    // Disable output buffering
    cout << std::unitbuf;
    cerr << std::unitbuf;

    Server server; // If it throws exception here, of course the program can't run

    try {
        server.set_socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

        const auto reuse = "1";
        server.set_reusable(SOL_SOCKET, SO_REUSEADDR, reuse, sizeof(reuse));

        constexpr int max_connections = 5;
        server.set_server_ip(AF_INET, INADDR_ANY, 9092).bind_s().listen_s(max_connections);

    } catch (const std::exception& e) {
        Logger::print_current_time(cerr);
        cerr << std::format("[Server]: {}\n", e.what());
        return 1;
    }

    Client client;

    try {
        client.accept_c(server.get_socket());

    } catch (const std::exception& e) {
        Logger::print_current_time(cerr);
        cerr << std::format("[Client]\t{}\n", e.what());
        return 1;
    }

    server.close_s();
    client.close_c();

    return 0;
}


