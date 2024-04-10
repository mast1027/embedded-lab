cmake_minimum_required(VERSION 3.25)
project(embedded_lab)

set(CMAKE_CXX_STANDARD 17)

add_executable(embedded_lab main.cpp
        Satellite.cpp
        Satellite.h
        SatelliteNetwork.cpp
        SatelliteNetwork.h
        globals.h
        globals.cpp
        globals.h)
