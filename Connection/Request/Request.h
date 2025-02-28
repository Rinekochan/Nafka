//
// Created by hoang on 28/02/2025.
//

#pragma once
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace Nafka::Connection {
    struct RequestHeader {
        uint16_t request_api_key{};
        uint16_t request_api_version{};
        uint32_t correlation_id{};
        uint32_t client_id;
        std::vector<uint8_t> TAG_BUFFER{};

        RequestHeader() = default;

        void deserialize(std::vector<uint8_t>& data);
    };

    struct RequestBody {};

    struct Request {
        uint32_t message_size{};
        RequestHeader header;
        RequestBody body;

        Request() = default;
        Request(const RequestHeader& header, const RequestBody& body);

        void deserialize(std::vector<uint8_t>& data);

        friend void operator<<(std::ostream& os, const Request& request);
    };
} // namespace Nafka::Connection
