﻿#pragma once
#include <chrono>
#include <iostream>

namespace Logger {
    static void print_current_time(std::ostream& os = std::cout) {
        using namespace std::chrono;

        time_point t_p{system_clock::now()};
        tm t_container;

        const time_t time{system_clock::to_time_t(t_p)};

        localtime_s(&t_container, &time);
        os << std::put_time(&t_container, "[%c] ");
    }

    template<typename T>
    static void print_log(T&& content, std::ostream& os = std::cout) {
        os << content;
    }

    template<typename T>
    static void print_log(T& content, std::ostream& os = std::cout) {
        os << content;
    }
}
