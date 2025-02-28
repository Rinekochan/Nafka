//
// Created by hoang on 28/02/2025.
//

#include "Request.h"

#include "../../Logger/Logger.h"
#include "../Helper/Helper.h"

using namespace Nafka::Connection;

// define constructors
Request::Request(const RequestHeader& header, const RequestBody& body)
    : header(header), body(body) {}

Request::Request(std::vector<uint8_t> data) {
    deserialize(data);
}

// define deserialize functions
void RequestHeader::deserialize(std::vector<uint8_t>& data, size_t& offset) {
    Helper::deserialize_bytes(request_api_key, offset, data, sizeof(request_api_key));
    Helper::deserialize_bytes(request_api_version, offset, data, sizeof(request_api_version));
    Helper::deserialize_bytes(correlation_id, offset, data, sizeof(correlation_id));
    Helper::deserialize_bytes(client_id, offset, data, sizeof(client_id));

    while (data.size() > 0) {
        TAG_BUFFER.push_back(data.front());
        data.pop_back();
    }
}

void Request::deserialize(std::vector<uint8_t>& data) {
    try {
        size_t offset = 0;
        Helper::deserialize_bytes(message_size, offset, data, sizeof(message_size));
        header.deserialize(data, offset);
    } catch (const std::exception& e) {
        Logger::print_current_time(std::cerr);
        Logger::print_log(std::format("[Server]: {}", e.what()));
    }
}

std::string Request::to_string() const {
    return std::format("\"message_size\": {},\n\"request_api_key\": {},\n"
                       "\"request_api_version\": {},\n\"correlation_id\": {},\n\"client_id\": {}",
                       message_size, header.request_api_key, header.request_api_version, header.correlation_id, header.client_id);
}
