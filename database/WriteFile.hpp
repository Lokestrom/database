/*
Athor: Loke Strøm
*/
#pragma once

#include "Vector.hpp"
#include "String.hpp"

namespace Database
{
    template<typename T>
    class WriteFile
    {
    private:
        const char splitByte = char(178);
        std::ofstream* file;
        Vector<char>* buffer;

    public:
        WriteFile();
        WriteFile(String file);

        ~WriteFile();

        void open(String file);

        void addcolumns(Vector<String> columnNames);

        void addData(Vector<T> data);
        void addData(T data);
    };
}

#include "WriteFile.tpp"