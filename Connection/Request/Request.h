//
// Created by hoang on 28/02/2025.
//

#pragma once
#include <cstdint>
#include <string>
#include <vector>

namespace Nafka::Connection {
    struct RequestHeader {
        uint16_t request_api_key{0};
        uint16_t request_api_version{0};
        uint32_t correlation_id{0};
        uint32_t client_id;
        std::vector<uint8_t> TAG_BUFFER{};

        RequestHeader() = default;

        void deserialize(std::vector<uint8_t>& data, size_t& offset);
    };

    struct RequestBody {};

    struct Request {
        uint32_t message_size{0};
        RequestHeader header{};
        RequestBody body{};

        Request() = default;
        Request(const RequestHeader& header, const RequestBody& body);
        explicit Request(std::vector<uint8_t> data);

        void deserialize(std::vector<uint8_t>& data);

        [[nodiscard]] std::string to_string() const;
    };
} // namespace Nafka::Connection
