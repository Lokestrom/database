/*
Athor: Loke Str�m
*/
#pragma once

#include "String.hpp"
#include "Vector.hpp"

namespace Database
{
    template <typename T>
    class ReadFile
    {
    private:
        std::ifstream* file;
        String fileName;
        unsigned int dataStart;
        Vector<String> ColumnNames;
        const char splitByte = char(178);

    public:
        ReadFile();
        ReadFile(String fileName);
        ~ReadFile();

        void getAllDataFromColumn(Vector<T>& data, String columnName) noexcept;
        void getAllRowsWhereColumnIsEqualeToAValue(Vector<Vector<T>>& data, String columnName, T value) noexcept;
        void getRow(Vector<T>& data, unsigned int row) noexcept;
        void getAllData(Vector<Vector<T>>& data) noexcept;
    };
}

#include "ReadFile.tpp"