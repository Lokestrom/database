/*
Athor: Loke Strøm
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
        ReadFile(const String& fileName);
        ~ReadFile();

        void open(const String& fileName);
        void close();
        bool isOpen();

        void getAllDataFromColumn(const Vector<T>& data, const String& columnName) noexcept;
        void getAllRowsWhereColumnIsEqualeToAValue(const Vector<Vector<T>>& data, const String& columnName, T value) noexcept;
        void getRow(const Vector<T>& data, unsigned int row);
        void getAll(const Vector<Vector<T>>& data) noexcept;

        Vector<String> getColumnNames() noexcept;
    };
}

#include "TemplateFiles/ReadFile.tpp"