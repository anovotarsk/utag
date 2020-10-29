cmake_minimum_required(VERSION 3.18)

project(utag CXX)

#list(APPEND CMAKE_PREFIX_PATH "~/.brew/Cellar/qt/5.15.1/")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5Widgets)

include_directories(taglib app/src)

add_compile_options(-std=c++17)

add_executable(${PROJECT_NAME} app/main.cpp app/resources/mainwindow.ui)

add_subdirectory(taglib)
add_subdirectory(app/src)

target_link_libraries(${PROJECT_NAME} utag_lib)
target_link_libraries(${PROJECT_NAME} taglib)

target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
