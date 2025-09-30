cmake_minimum_required(VERSION 4.1)

project(Database)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

file(GLOB SOURCES "database/src/*.cpp")

add_library(Database STATIC ${SOURCES})

target_include_directories(Database
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/database/include
)