# Database
A library for some data structures and storing data.<br>
### [Documentation for Database](https://github.com/Lokestrom/documentationForCPP)
### It contains these classes:
* Exception
* String
* Vector
* Queue
* WriteFile
* ReadFile
* EditFile
* CSV conversions


## Building, Testing and Using
The project uses CMake and requires C++ 20 or later. There is for now no precompiled version of the library, 
so you need to build it from source. There may come some release versions with precompiled binaries in the future.
<br><br>
To build the project and test it, follow these steps:

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
    ```