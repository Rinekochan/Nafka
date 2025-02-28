//
// Created by hoang on 28/02/2025.
//

#include "Response.h"

#include <stdexcept>

#include "../Helper/Helper.h"

namespace Nafka::Connection {
    // Define constructors
    ResponseHeader::ResponseHeader(const uint32_t correlation_id)
        : correlation_id(correlation_id){}

    Response::Response(const ResponseHeader& header, const ResponseBody& body)
        : header(header), body(body) {}

    // Define serialization functions
    std::vector<uint8_t> ResponseHeader::serialize() const {
        std::vector<uint8_t> bi_data;

        Helper::serialize_bytes(correlation_id, bi_data, sizeof(correlation_id));

        return bi_data;
    }

    std::vector<uint8_t> Response::serialize() const {
        std::vector<uint8_t> bi_data;

        Helper::serialize_bytes(message_size, bi_data, sizeof(message_size));

        auto header_data = header.serialize();
        bi_data.insert(std::end(bi_data), std::begin(header_data), std::end(header_data));

        return bi_data;
    }

    void operator<<(std::ostream& stream, Response& response) {
         stream << std::format("\n\"message_size\": {},\n\"correlation_id\": {}\n",
             response.message_size, response.header.correlation_id);
    }
}