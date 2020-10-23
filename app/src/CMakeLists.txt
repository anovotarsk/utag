cmake_minimum_required(VERSION 3.18)
project(utag_lib)

include_directories(.)

add_library(utag_lib tags.cpp strsplit.cpp mainwindow.cpp read_directory.cpp)

target_link_libraries(${PROJECT_NAME} Qt5::Widgets)