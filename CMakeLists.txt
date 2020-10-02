cmake_minimum_required(VERSION 3.18)

project(utag CXX)

include_directories(taglib)

add_compile_options(-std=c++17)

add_executable(utag app/main.cpp)

add_subdirectory(taglib)

target_link_libraries(utag taglib)