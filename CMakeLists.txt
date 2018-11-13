cmake_minimum_required(VERSION 3.12)
project(Cryptographic_algorithms)

set(CMAKE_CXX_STANDARD 14)

add_executable(Cryptographic_algorithms src/main.cpp src/BigInteger.cpp src/BigInteger.h src/Algorithms.cpp src/Algorithms.h)