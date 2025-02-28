//
// Created by hoang on 28/02/2025.
//

#include "Request.h"

#include "../../Logger/Logger.h"
#include "../Helper/Helper.h"

namespace Nafka::Connection {
    // define constructors
    Request::Request(const RequestHeader& header, const RequestBody& body)
        : header(header), body(body) {}

    // define deserialize functions
    void RequestHeader::deserialize(std::vector<uint8_t>& data) {
        Helper::deserialize_bytes(request_api_key, data, sizeof(request_api_key));
        Helper::deserialize_bytes(request_api_version, data, sizeof(request_api_version));
        Helper::deserialize_bytes(correlation_id, data, sizeof(correlation_id));
        Helper::deserialize_bytes(client_id, data, sizeof(client_id));

        while (data.size() > 0) {
            TAG_BUFFER.push_back(data.front());
            data.pop_back();
        }
    }

    void Request::deserialize(std::vector<uint8_t>& data) {
        try {
            Helper::deserialize_bytes(message_size, data, sizeof(message_size));
            header.deserialize(data);
        } catch (const std::exception& e) {
            Logger::print_current_time(std::cerr);
            Logger::print_log(std::format("[Server]: {}", e.what()), std::cerr);
        }
    }

}