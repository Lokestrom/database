/*
Athor: Loke Strøm
*/
#pragma once

#include "Vector.hpp"
#include "String.hpp"

namespace Database
{
    template<typename T>
    class EditFile
    {
    private:
        String _fileName;
        Vector<String> columnNames;
        size_t dataStart;
        const char splitByte = char(178);


    public:
        EditFile();
        EditFile(String fileName);

        void open(String fileName);
        void close();

        void EditCell(T data, String column, size_t row);
        void EditRow(Vector<T> data, size_t row);

        Vector<size_t> SearchInColumn(T data, String column);
    };
}

#include "TemplateFiles/EditFile.tpp"