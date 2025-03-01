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

    struct ResponseApiBody {
        uint8_t api_keys_length{0x02};
        uint16_t api_key{};
        uint16_t min_version{};
        uint16_t max_version{};
        uint8_t api_key_tags{0x00};

        ResponseApiBody() = default;

        ResponseApiBody(uint16_t api_key, uint16_t min_version, uint16_t max_version);

        [[nodiscard]] std::vector<uint8_t> serialize() const;
    };

    struct ResponseBody {
        uint16_t error_code{0};
        std::vector<ResponseApiBody> api_body;
        uint32_t throttle_time_ms{0};
        uint8_t no_tags{0x00};

        ResponseBody() = default;

        explicit ResponseBody(uint16_t error_code);

        void add_api(ResponseApiBody api);

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
