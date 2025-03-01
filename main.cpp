#include <format>
#include <future>
#include <iostream>

#include "Client/Client.h"
#include "Connection/Connection/Connection.h"
#include "Logger/Logger.h"
#include "Server/Server.h"


int main(int argc, char* argv[]) {
    using std::cout, std::cerr, Nafka::Server, Nafka::Client;
    using namespace Nafka::Connection;

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

    std::vector<std::future<void>> futures;

    while (true) {
        try {
            client.accept_c(server.get_socket());

        } catch (const std::exception& e) {
            Logger::print_current_time(cerr);
            Logger::print_log(std::format("[Client]\t{}\n", e.what()), cerr);
            client.close_c();
            continue;
        }

        auto handle_clients = [](const SOCKET& socket) {
            Connection connection;
            connection.bind_client_socket(std::move(socket));
            while (true) {
                try {
                    connection.handle_requests();
                } catch (const std::exception& e) {
                    Logger::print_current_time(cerr);
                    Logger::print_log(std::format("[Client]\t{}\n", e.what()), cerr);
                    break;
                }
            }
        };

        futures.emplace_back(std::async(std::launch::async, handle_clients, client.get_socket())); // add new task asynchronously

        std::erase_if(futures, [](const std::future<void> &f) { // delete any tasks if it's idle
           return f.wait_for(std::chrono::seconds(0)) == std::future_status::ready;
        });
    }

    server.close_s();

    return 0;
}


