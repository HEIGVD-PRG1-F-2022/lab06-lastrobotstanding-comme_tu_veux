cmake_minimum_required(VERSION 3.23)
project(Robot)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent) # once in the project to include the module

FetchContent_Declare(librobots
        GIT_REPOSITORY https://github.com/HEIGVD-PRG1-F-2022/librobots.git
        GIT_TAG v0.2.3
        )
FetchContent_MakeAvailable(librobots)

FetchContent_Declare(libdio
        GIT_REPOSITORY https://github.com/HEIGVD-PRG1-F-2022/libdio.git
        GIT_TAG v0.2.1
        )
FetchContent_MakeAvailable(libdio)

add_executable(Robot main.cpp robots/sonny_robot.cpp robots/sonny_robot.h game.cpp game.h point.h action.cpp action.h point.cpp robot_state.cpp robot_state.h)

target_link_libraries(Robot PRIVATE libdio)
target_link_libraries(Robot PRIVATE librobots)