cmake_minimum_required(VERSION 3.30)
project(Nafka)

set(CMAKE_CXX_STANDARD 23)

add_executable(Nafka main.cpp
        Server/Server.cpp
        Server/Server.h
        Client/Client.cpp
        Client/Client.h
        Logger/Logger.h)
if(WIN32)
    target_link_libraries(Nafka ws2_32)
endif()