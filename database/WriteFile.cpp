/*
Athor: Loke Strøm
Created: 12 apr 2022
*/

#include "WriteFile.hpp"

namespace Database
{
    //defalt constructor
    WriteFile::WriteFile()
    {
        std::cout << std::fixed;
    }

    //constructor opens file
    WriteFile::WriteFile(String filename)
    {
        WriteFile::filename = filename + ".db";
        file->open(WriteFile::filename.data());
        std::cout << std::fixed;
    }

    WriteFile::~WriteFile()
    {
        if (file->is_open())
            file->close();
        delete file;
    }

    void WriteFile::openFile(String filename)
    {
        WriteFile::filename = filename + ".db";
        file->open(WriteFile::filename.data());
    }

    //add's a column to the file
    void WriteFile::addColumn(String columnName)
    {
        if (!file->is_open())
        {
            errorMsg("No file is open", "addColumn", {columnName});
            return;
        }
        if (addedData)
        {
            errorMsg("Can't add column data has been added", "addColumn", {columnName});
            return;
        }
        columnNumber++;
        if (columnNumber == 1)
        {
            *file << columnName;
            return;
        }
        *file << splitElementForDatabase << columnName;
    }

    //add's an array of column's to the file
    void WriteFile::addColumnVector(Vector<String> columnNames)
    {
        if (!file->is_open())
        {
            errorMsg("No file is open", "addColumnArray", columnNames);
            return;
        }
        if (addedData)
        {
            errorMsg("Can't add column data has been added", "addColumnArray", columnNames);
            return;
        }
        for (String columnName : columnNames)
        {
            columnNumber++;
            if (columnNumber == 1)
                *file << columnName;
            else
                *file << splitElementForDatabase << columnName;
        }
    }

    void WriteFile::addNewLine()
    {
        if (!file->is_open())
        {
            errorMsg("No file is open", "addNewLine", {});
            return;
        }
        if (columnNumber > dataPointsOnLine)
        {
            errorMsg("More columns then data, Column count: " + toS(columnNumber) + " Data count: " + toS(dataPointsOnLine), "addDataVector", {});
            return;
        }
        else if (columnNumber < dataPointsOnLine)
        {
            errorMsg("Less columns then data, Column count: " + toS(columnNumber) + " Data count: " + toS(dataPointsOnLine), "addDataVector", {});
            return;
        }
        dataPointsOnLine = 0;
        *file << std::endl;
    }
}
