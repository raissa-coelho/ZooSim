cmake_minimum_required(VERSION 3.22)
project(ZooSim C)

set(CMAKE_C_STANDARD 11)

include_directories(print data sim)

add_executable(ZooSim
        print/print.c
        print/print.h
        tema1.c
        data/data.c
        data/data.h
        sim/simulation.h
        sim/simulation.c)
