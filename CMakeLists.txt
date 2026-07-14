cmake_minimum_required(VERSION 4.3)
project(KWC C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(WLROOTS REQUIRED wlroots-0.20>=0.20.2)
pkg_check_modules(PIXMAN REQUIRED pixman-1)

add_executable(KWC src/server.c
        src/client.c)
