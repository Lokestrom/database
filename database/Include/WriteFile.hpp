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

    public:
        WriteFile();
        WriteFile(String filename);

        ~WriteFile();

        void open(String filename);
        void close();

        void addcolumns(Vector<String> columnNames);

        void addData(Vector<T> data);
    };
}

#include "TemplateFiles/WriteFile.tpp"