//
// Created by hoang on 28/02/2025.
//

#pragma once
#include <concepts>
#include <cstdint>
#include <stdexcept>
#include <vector>

#include "../../Logger/Logger.h"

namespace Nafka::Helper {
    template<typename T>
    requires std::integral<T>
    void serialize_bytes(const T data, std::vector<uint8_t>& bi_data, const size_t amt_bytes) {
        if (amt_bytes == 0) throw std::invalid_argument("Invalid amount of bytes to serialize");

        int cur_bytes = amt_bytes - 1;
        while (cur_bytes >= 0) {
            bi_data.push_back((data >> (cur_bytes * 8)) & 0xFF);
            cur_bytes -= 1;
        }
    }

    template<typename T>
    requires std::integral<T>
    void deserialize_bytes(T& field, size_t& data_it, std::vector<uint8_t>& bi_data, const size_t amt_bytes) {
        if (amt_bytes == 0) throw std::invalid_argument("Invalid amount of bytes to deserialize");

        for (size_t i = 0; i < amt_bytes; ++i) {
            field = field << 8 | bi_data[data_it++];
        }
    }
}
