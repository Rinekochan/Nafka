//
// Created by hoang on 28/02/2025.
//

#include "Response.h"

#include <format>

#include "../Helper/Helper.h"

using namespace Nafka::Connection;

// Define constructors
ResponseHeader::ResponseHeader(const uint32_t correlation_id)
    : correlation_id(correlation_id){}

ResponseBody::ResponseBody(const uint16_t error_code)
    : error_code(error_code){}

Response::Response(const ResponseHeader& header, const ResponseBody& body)
    : header(header), body(body) {}

// Define serialization functions
std::vector<uint8_t> ResponseHeader::serialize() const {
    std::vector<uint8_t> bi_data;

    Helper::serialize_bytes(correlation_id, bi_data, sizeof(correlation_id));

    return bi_data;
}

std::vector<uint8_t> ResponseBody::serialize() const {
    std::vector<uint8_t> bi_data;

    Helper::serialize_bytes(error_code, bi_data, sizeof(error_code));

    return bi_data;
}

std::vector<uint8_t> Response::serialize() const {
    std::vector<uint8_t> bi_data;

    Helper::serialize_bytes(message_size, bi_data, sizeof(message_size));

    auto header_data = header.serialize();
    bi_data.insert(std::end(bi_data), std::begin(header_data), std::end(header_data));

    auto body_data = body.serialize();
    bi_data.insert(std::end(bi_data), std::begin(body_data), std::end(body_data));

    return bi_data;
}

std::string Response::to_string() const {
    return std::format("\"message_size\": {},\n\"correlation_id\": {},\n\"error_code\": {}",
        message_size, header.correlation_id, body.error_code);
}