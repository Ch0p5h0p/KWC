cmake_minimum_required(VERSION 4.3)
project(KWC C)

set(CMAKE_C_STANDARD 11)

add_executable(KWC src/server.c
        src/client.c)
