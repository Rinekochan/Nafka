//
// Created by hoang on 28/02/2025.
//

#pragma once
#include <cstdint>
#include <ostream>
#include <vector>

namespace Nafka::Connection {
    struct ResponseHeader {
        uint32_t correlation_id{0};

        ResponseHeader() = default;

        explicit ResponseHeader(uint32_t correlation_id);

        [[nodiscard]] std::vector<uint8_t> serialize() const;
    };

    struct ResponseBody {
        uint16_t error_code{0};

        ResponseBody() = default;

        explicit ResponseBody(uint16_t error_code);

        [[nodiscard]] std::vector<uint8_t> serialize() const;
    };

    struct Response {
        uint32_t message_size{0};
        ResponseHeader header;
        ResponseBody body;

        Response(const ResponseHeader& header, const ResponseBody& body);

        [[nodiscard]] std::vector<uint8_t> serialize() const;

        [[nodiscard]] std::string to_string() const;
    };
} // namespace Nafka::Connection
