#pragma once
#include <memory>
#include <vector>
#include "../Response/Response.h"
#include "../Request/Request.h"
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

namespace Nafka::Connection {
    class Connection {
    public:
        Connection() = default;
        void bind_client_socket(const SOCKET&& socket);
        void handle_requests() const;
        void send_responses(const Request& request) const;

    private:
        std::unique_ptr<SOCKET> client_socket;

        std::vector<uint8_t> receive_data() const;
        void send_data(const std::vector<uint8_t>& data) const;
    };
}
