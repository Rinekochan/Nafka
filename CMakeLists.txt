cmake_minimum_required(VERSION 3.30)
project(Nafka)

set(CMAKE_CXX_STANDARD 23)

add_executable(Nafka main.cpp
        Server/Server.cpp
        Server/Server.h
        Client/Client.cpp
        Client/Client.h
        Logger/Logger.h
        Connection/Response/Response.cpp
        Connection/Response/Response.h
        Connection/Helper/Helper.h
        Connection/Request/Request.cpp
        Connection/Request/Request.h
        Connection/Connection/Connection.cpp
        Connection/Connection/Connection.h
        Connection/Api/ApiFactory.h
        Connection/Api/Api.h)
if(WIN32)
    target_link_libraries(Nafka ws2_32)
endif()