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
        void EditColumn(Vector<T> data, String name);

        void insertRow(Vector<T> data, size_t row);
        void insertColumn(Vector<T> data, String name);

        void popRow(size_t row);
        void popColumn(String name);

        Vector<size_t> SearchInColumn(T target, String column);
        Vector<Vector<size_t>> Search(T target);
        size_t getRowAmount();

    };
}

#include "TemplateFiles/EditFile.tpp"