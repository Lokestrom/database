# Database
A lightweight C++ library providing a collection of data structures and utilities for working with data.
### [Documentation for Database](https://github.com/Lokestrom/documentationForCPP)
### It contains these classes:
* String
* CharSpan
* Vector
* HeapArray
* Queue
* AtomicStaticQueue(SPSC)
* WriteFile
* ReadFile

## Building, Testing and Using
The project uses CMake and requires C++ 23 or later.
<br>
#### To build the project and test it, follow these steps:

- Clone the repository:
    ```bash
    git clone https://github.com/Lokestrom/database.git
    ```
- build the project using CMake(4.1 or greater):
    ```bash
    cd database
    mkdir build
    cd build
    cmake ..
    cmake --build . --config <configuration>
    ```
- Run tests:
    ```bash
    ctest -C <configuration>
    ```
- Use the library in your project using CMake:
    ```cmake
    add_subdirectory(<path to Database>)
    target_link_libraries(<your target> Database)
    
    # Optional configuration flags (use only one or none)
    option(FORCE_THROW_EXCEPTION "Force exception throwing" OFF)
    option(FORCE_RETURN_EXCEPTIONS "Force return-based exceptions where possible" OFF)
    ```

## Notes
* Not all components are fully tested.
* Builds have been verified on Clang and MSVC.
* When compiling without exceptions, the library automatically switches to return-based error handling.
However, functions returning `std::expected` may still throw internally and call `std::terminate` if needed.