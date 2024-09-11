cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

project(pbf_group_test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SERVER
    "src/server/main.cpp"
    "src/server/server.cpp"
    )

file(GLOB CLIENT
    "src/client/main.cpp"
    "src/client/client.cpp"
    )

add_executable(server ${SERVER})
add_executable(client ${CLIENT})