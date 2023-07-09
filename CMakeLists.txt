cmake_minimum_required(VERSION 3.25)
project(n_body_simulations)

set(CMAKE_CXX_STANDARD 14)

# add_library(n_body_simulations, yaml-cpp, data_reader.cpp)

add_executable(n_body_simulations
        particle.cpp)
