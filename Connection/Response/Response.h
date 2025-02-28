//
// Created by hoang on 28/02/2025.
//

#pragma once
#include <cstdint>
#include <ostream>
#include <vector>

namespace Nafka::Connection {
    struct ResponseHeader {
        uint32_t correlation_id{};

        explicit ResponseHeader(uint32_t correlation_id);

        [[nodiscard]] std::vector<uint8_t> serialize() const;
    };

    struct ResponseBody {
        ResponseBody() = default;
    };

    struct Response {
        uint32_t message_size{0};
        ResponseHeader header;
        ResponseBody body;

        Response(const ResponseHeader& header, const ResponseBody& body);

        [[nodiscard]] std::vector<uint8_t> serialize() const;

        friend void operator<<(std::ostream& stream, Response& response);
    };
} // namespace Nafka::Connection
