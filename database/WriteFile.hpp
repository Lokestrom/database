/*
Athor: Loke Strøm
*/
#pragma once

#include "Vector.hpp"
#include "String.hpp"
#include "Queue.hpp"
#include <atomic>
#include <thread>

namespace Database
{
    template<typename T>
    class WriteFile
    {
    private:
        const char splitByte = char(178);
        std::ofstream* file;
        Queue<char>* buffer;
        std::thread* tWrite;
        std::atomic<bool> joined;

        void write();

    public:
        WriteFile();
        WriteFile(String file);

        ~WriteFile();

        void open(String file);
        void close();

        void addcolumns(Vector<String> columnNames);

        void addData(Vector<T> data);
    };
}

#include "WriteFile.tpp"