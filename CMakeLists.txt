cmake_minimum_required(VERSION 4.1)

project(Database)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS OFF)

option(FORCE_THROW_EXCEPTION "Forces throwing" OFF)
option(FORCE_RETURN_EXCEPTIONS "Forces return exceptions where posible" OFF)

include(CheckCXXSourceCompiles)

check_cxx_source_compiles("
    int main() {
        try { throw 1; }
        catch(...) {}
        return 0;
    }
" EXCEPTIONS_ENABLED)


file(GLOB SOURCES "src/*.cpp")

add_library(Database STATIC ${SOURCES})

set_property(TARGET Database PROPERTY COMPILE_WARNING_AS_ERROR ON)

if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
	target_compile_options(Database PUBLIC /std:c++23)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	if (CMAKE_CXX_COMPILER_FRONTEND_VARIANT MATCHES "MSVC")
		target_compile_options(Database PUBLIC /std:c++23)
	else()
		target_compile_options(Database PUBLIC -std=c++23)
	endif()
elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
	target_compile_options(Database PUBLIC -std=gnu++23)
endif()

if (FORCE_RETURN_EXCEPTIONS AND FORCE_THROW_EXCEPTION)
    message(FATAL_ERROR "Cannot set both FORCE_RETURN_EXCEPTIONS and FORCE_THROW_EXCEPTION")
endif()

if (EXCEPTIONS_ENABLED AND (NOT FORCE_RETURN_EXCEPTIONS OR FORCE_THROW_EXCEPTION))
    message(STATUS "Exceptions: ENABLED")
    target_compile_definitions(Database PUBLIC DATABASE_EXCEPTIONS_ENABLED=1)
else()
    message(STATUS "Exceptions: DISABLED")
    target_compile_definitions(Database PUBLIC DATABASE_EXCEPTIONS_ENABLED=0)
endif()

# tests must be compiled without return exceptions
enable_testing()

set(tests 
tests/vectorTests.cpp
tests/stringTests.cpp
tests/readFileTests.cpp
tests/writeFileTests.cpp
tests/queueTests.cpp
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
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/Database")
endforeach()
