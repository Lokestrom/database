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
        WriteFile(const String& filename);

        ~WriteFile();

        void open(const String& filename);
        void close();

        void addcolumns(const Vector<String>& columnNames);

        void addData(const Vector<T>& data);
    };
}

#include "TemplateFiles/WriteFile.tpp"