/*
Athor: Loke Strøm
Created: 12 apr 2022
*/

#include "WriteFile.hpp"

extern const std::string splitElement = "|";

extern bool terminateProgram = false;
extern bool terminateWriteFile = false;
extern bool errorHasBeenThrown = false;
extern bool NANinData = false;

namespace Database
{
    using namespace DatabaseFung;

    //defalt constructor
    WriteFile::WriteFile()
    {
        std::cout << std::fixed;
    }

    //constructor opens file
    WriteFile::WriteFile(std::string filename)
    {
        WriteFile::filename = filename;
        file->open(filename);
        std::cout << std::fixed;
    }

    WriteFile::~WriteFile()
    {
        if (file->is_open())
            file->close();
        delete file;
        if (errorHasBeenThrown && terminateWriteFile)
            remove(filename.c_str());
    }

    void WriteFile::openFile(std::string filename)
    {
        WriteFile::filename = filename;
        file->open(filename);
    }

    void WriteFile::errorMsg(const char* ErrorMsg_, const char* ErrorFungtion, std::vector<const char*> ErrorFungtionInput)
    {
        DatabaseFung::errorMsg("Database::WriteFile", ErrorMsg_, ErrorFungtion, ErrorFungtionInput);
    }

    //add's a column to the file
    void WriteFile::addColumn(std::string columnName)
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
        *file << "|" << columnName;
    }

    //add's an array of column's to the file
    void WriteFile::addColumnVector(std::vector<std::string> columnNames)
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
        for (std::string columnName : columnNames)
        {
            columnNumber++;
            if (columnNumber == 1)
                *file << columnName;
            else
                *file << "|" << columnName;
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
