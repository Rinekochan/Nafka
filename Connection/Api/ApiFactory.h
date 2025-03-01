#pragma once
#include <functional>

#include "../Request/Request.h"
#include "../Response/Response.h"
#include "Api.h"

namespace Nafka::Connection {
    namespace ApiFactory {
        inline std::function<Response(Request)> getApiResponseFunc(const uint16_t request_api_key) {
            switch (static_cast<int>(request_api_key)) {
                case static_cast<int>(ApiKey::ApiVersion):
                    return Api::processApiVersionsRequest;
                default:
                    throw std::runtime_error("Invalid request API key");
            }
        }
    }
}
