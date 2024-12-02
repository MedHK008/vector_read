cmake_minimum_required(VERSION 3.5.0)
project(vector_read VERSION 0.1.0 LANGUAGES C CXX)

add_executable(vector_read main.cpp Reader.h Reader.cpp MappedReader.h MappedReader.cpp)

