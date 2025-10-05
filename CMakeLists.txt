cmake_minimum_required(VERSION 4.1)

project(Database)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

file(GLOB SOURCES "src/*.cpp")

add_library(Database STATIC ${SOURCES})

enable_testing()

set(tests 
tests/vectorTests.cpp
tests/stringTests.cpp
)

set (testNames "")

foreach(test ${tests})
    get_filename_component(testName ${test} NAME_WE)
    add_executable(${testName} ${test})
    target_link_libraries(${testName} PRIVATE Database)
    add_test(NAME ${testName} COMMAND ${testName})
    list(APPEND testNames ${testName})
endforeach()

set(targets Database ${testNames})

foreach(target ${targets})
    target_include_directories(${target}
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/Database)
endforeach()