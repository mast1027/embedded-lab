cmake_minimum_required(VERSION 3.25)
project(embedded_lab)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -pg")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -pg")

add_executable(embedded_lab main.cpp
        Satellite.cpp
        Satellite.h
        SatelliteNetwork.cpp
        SatelliteNetwork.h
        globals.h
        globals.cpp
        globals.h
        timer.cpp
        timer.h)
