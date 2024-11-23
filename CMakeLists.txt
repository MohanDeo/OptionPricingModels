cmake_minimum_required(VERSION 3.30)
project(MonteCarloOptionPricing)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(MonteCarloOptionPricing
    Option.cpp
    Option.h)
