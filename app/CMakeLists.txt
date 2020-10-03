cmake_minimum_required(VERSION 3.18)
project(utag_lib)

include_directories(src .)

add_library(utag_lib src/tags.cpp)