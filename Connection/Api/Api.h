#pragma once
#include "../Request/Request.h"
#include "../Response/Response.h"

namespace Nafka::Connection {
    enum class ApiKey {
        ApiVersion = 18
    };

    namespace Api {
        inline Response processApiVersionsRequest(const Request& request) {

            enum class ErrorCode {
                UNSUPPORTED_VERSION = 35
            };

            const auto header = ResponseHeader(request.header.correlation_id);
            auto body = ResponseBody();

            if (request.header.request_api_version < 0 || request.header.request_api_version > 4) {
                body.error_code = static_cast<uint16_t>(ErrorCode::UNSUPPORTED_VERSION);
            }

            return Response{header, body};
        }
    }
}