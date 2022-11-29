cmake_minimum_required(VERSION 3.23)
project(Robot)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent) # once in the project to include the module

FetchContent_Declare(libdio
        GIT_REPOSITORY https://github.com/HEIGVD-PRG1-F-2022/libdio.git
        GIT_TAG v0.1.10
        )
FetchContent_MakeAvailable(libdio)

add_executable(Robot main.cpp robots/SonnyRobot.cpp robots/SonnyRobot.h)

target_link_libraries(Robot PRIVATE libdio)