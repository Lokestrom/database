/*
Athor: Loke Strøm
Created: 12 apr 2022
*/

#include "ReadFile.hpp"

namespace Database
{
    using namespace DatabaseFung;
    void ReadFile::errorMsg(std::string ErrorMsg_, std::string ErrorFungtion, std::vector<std::string> ErrorFungtionInput)
    {
        DatabaseFung::errorMsg("Database::ReadFile", ErrorMsg_, ErrorFungtion, ErrorFungtionInput);
    }

    //constructer
    ReadFile::ReadFile(std::string fileName)
    {
        std::string text;
        ReadFile::filename = fileName;
        file->open(filename);
        getline(*file, text);

        for (std::string i : split(text, splitElement))
        {
            mapOfColumns[i] = nextColumnNumber;
            nextColumnNumber++;
        }
        file->close();
    }

    ReadFile::~ReadFile()
    {
        delete file;
    }

    //double version for graff thing
    std::vector<double> ReadFile::getAllDataFromColumnDouble(std::string columnName)
    {
        std::string text, token;
        if (!mapOfColumns.count(columnName))
        {
            errorMsg("Not a column name", "getAllDataFromColumnDouble", {columnName});
            return {};
        }
        std::vector<double> x;
        file->open(filename);
        firstLine = true;
        int l = 1;
        while (getline(*file, text))
        {
            if (!firstLine)
            {
                token = splitIndex(text, splitElement, mapOfColumns[columnName]);
                if (!canStringConvertToNumber(token))
                {
                    errorMsg("The column has a caracter at line: " + toS(l) + ". Can't convert to long double", "getAllDataFromColumnLongDouble", {columnName});
                    return {};
                }
                x.push_back(std::stold(token));
            }
            firstLine = false;
            l++;
        }
        file->close();
        return x;
    }

    //long double version for all other stuff
    std::vector<long double> ReadFile::getAllDataFromColumnLongDouble(std::string columnName)
    {
        if (!mapOfColumns.count(columnName))
        {
            errorMsg("Not a column name", "getAllDataFromColumnDouble", {columnName});
            return {};
        }
        std::string text, token;
        std::vector<long double> x;
        file->open(filename);
        firstLine = true;
        int l = 1;
        while (getline(*file, text))
        {
            if (!firstLine)
            {
                token = splitIndex(text, splitElement, mapOfColumns[columnName]);
                if (!canStringConvertToNumber(token))
                {
                    errorMsg("The column has a caracter at line: " + l, "getAllDataFromColumnLongDouble", {columnName});
                    return {};
                }
                x.push_back(std::stold(token));
            }
            firstLine = false;
            l++;
        }
        file->close();
        return x;
    }

    std::vector<std::string> ReadFile::getAllDataFromColumnString(std::string columnName)
    {
        if (!mapOfColumns.count(columnName))
        {
            errorMsg("Not a column name", "getAllDataFromColumnString", {columnName});
            return {};
        }
        std::string text;
        std::vector<std::string> x;
        file->open(filename);
        firstLine = true;
        while (getline(*file, text))
        {
            if (!firstLine)
            {
                x.push_back(splitIndex(text, splitElement, mapOfColumns[columnName]));
            }
            firstLine = false;
        }
        file->close();
        return x;
    }

    std::vector<std::vector<std::string>> ReadFile::getAllRowsWhereColumnIsEqualeToAValue(std::string columnName, std::string value)
    {
        if (!mapOfColumns.count(columnName))
        {
            errorMsg("Not a column name", "getAllRowsWhereColumnIsEqualeToAValue", {columnName, value});
            return {{}};
        }
        std::string text;
        file->open(filename);
        std::vector<std::vector<std::string>> x = {};
        firstLine = true;
        int j = 0, i = 0;
        while (getline(*file, text))
        {
            if (!firstLine)
            {
                x[i] = split(text, splitElement);
                if (x[mapOfColumns[columnName]][i] == value)
                {
                    i++;
                }
            }
            firstLine = false;
        }
        file->close();
        return x;
    }

    std::vector<std::string> ReadFile::getRow(int row)
    {
        std::string text;
        file->open(filename);
        for (int i = 0; i < row + 1; i++)
        {
            getline(*file, text);
        }
        file->close();
        return split(text, splitElement);
    }

    std::vector<std::vector<std::string>> ReadFile::getAllData()
    {
        std::string text;
        file->open(filename);
        std::vector<std::vector<std::string>> x = {};
        firstLine = true;
        while (getline(*file, text))
        {
            if (!firstLine)
            {
                x.push_back(split(text, splitElement));
            }
            firstLine = false;
        }
        file->close();
        return x;
    }
}