cmake_minimum_required(VERSION 3.17)
project(COMP5004HEGE)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(COMP5004HEGE
        main.cpp
        Room.cpp
        Room.h
        State.cpp
        State.h
        strings.h
        wordwrap.cpp
        wordwrap.h GameObject.cpp GameObject.h)
