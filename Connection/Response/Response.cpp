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

ResponseApiBody::ResponseApiBody(const uint16_t api_key, const uint16_t min_version, const uint16_t max_version)
    : api_key(api_key), min_version(min_version), max_version(max_version){}

ResponseBody::ResponseBody(const uint16_t error_code) : error_code(error_code) {}

void ResponseBody::add_api(const ResponseApiBody api) {
    api_body.push_back(api);
}

Response::Response(const ResponseHeader& header, const ResponseBody& body)
    : header(header), body(body) {}

// Define serialization functions
std::vector<uint8_t> ResponseHeader::serialize() const {
    std::vector<uint8_t> bi_data;

    Helper::serialize_bytes(correlation_id, bi_data, sizeof(correlation_id));

    return bi_data;
}

std::vector<uint8_t> ResponseApiBody::serialize() const {
    std::vector<uint8_t> bi_data;

    Helper::serialize_bytes(api_keys_length, bi_data, sizeof(api_keys_length));
    Helper::serialize_bytes(api_key, bi_data, sizeof(api_key));
    Helper::serialize_bytes(min_version, bi_data, sizeof(min_version));
    Helper::serialize_bytes(max_version, bi_data, sizeof(max_version));
    Helper::serialize_bytes(api_key_tags, bi_data, sizeof(api_key_tags));

    return bi_data;
}

std::vector<uint8_t> ResponseBody::serialize() const {
    std::vector<uint8_t> bi_data;

    Helper::serialize_bytes(error_code, bi_data, sizeof(error_code));

    std::for_each(std::begin(api_body), std::end(api_body), [&bi_data](const ResponseApiBody& api) {
        auto api_body_data = api.serialize();
        bi_data.insert(std::end(bi_data), std::begin(api_body_data), std::end(api_body_data));
    });

    Helper::serialize_bytes(throttle_time_ms, bi_data, sizeof(throttle_time_ms));
    Helper::serialize_bytes(no_tags, bi_data, sizeof(no_tags));

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