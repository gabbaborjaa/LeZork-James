cmake_minimum_required(VERSION 3.29)
project(LeZork_James)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(LeZork_James
    game.hpp
    item.hpp
    Location.hpp
    main.cpp
    npc.hpp)
