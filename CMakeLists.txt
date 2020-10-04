cmake_minimum_required(VERSION 3.18)

project(utag CXX)

#list(APPEND CMAKE_PREFIX_PATH "~/.brew/Cellar/qt/5.15.1/")

include_directories(taglib app/src)

add_compile_options(-std=c++17)

add_executable(utag app/main.cpp)

add_subdirectory(taglib)
add_subdirectory(app/src)

target_link_libraries(utag utag_lib)
target_link_libraries(utag taglib)