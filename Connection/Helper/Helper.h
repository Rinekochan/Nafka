//
// Created by hoang on 28/02/2025.
//

#pragma once
#include <bits/ranges_algo.h>
#include <concepts>
#include <cstdint>
#include <format>
#include <numeric>
#include <stdexcept>
#include <vector>

namespace Nafka::Helper {
    template<typename T>
    requires std::integral<T>
    void serialize_bytes(const T data, const std::vector<uint8_t>& bi_data, const size_t amt_bytes) {
        if (amt_bytes == 0) throw std::invalid_argument("Invalid amount of bytes to serialize");

        int cur_bytes = amt_bytes - 1;
        while (cur_bytes >= 0) {
            bi_data.push_back((data >> (cur_bytes * 8)) & 0xFF);
            cur_bytes -= 1;
        }
    }

}
