/*
Athor: Loke Strøm
*/

#include "ReadFile.hpp"
#include "String.hpp"

namespace Database
{
    using namespace DatabaseFung;
    void ReadFile::errorMsg(String ErrorMsg_, String ErrorFungtion, Vector<String> ErrorFungtionInput)
    {
        DatabaseFung::errorMsg("Database::ReadFile", ErrorMsg_, ErrorFungtion, ErrorFungtionInput);
    }

    //constructer
    ReadFile::ReadFile(String fileName)
    {
        String text;
        ReadFile::filename = fileName;
        file->open(filename);
        getline(*file, text);

        for (String i : split(text, splitElement))
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
    Vector<double> ReadFile::getAllDataFromColumnDouble(String columnName)
    {
        String text, token;
        if (!mapOfColumns.count(columnName))
        {
            errorMsg("Not a column name", "getAllDataFromColumnDouble", {columnName});
            return {};
        }
        Vector<double> x;
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
                x.push_back(stold(token));
            }
            firstLine = false;
            l++;
        }
        file->close();
        return x;
    }

    //long double version for all other stuff
    Vector<long double> ReadFile::getAllDataFromColumnLongDouble(String columnName)
    {
        if (!mapOfColumns.count(columnName))
        {
            errorMsg("Not a column name", "getAllDataFromColumnDouble", {columnName});
            return {};
        }
        String text, token;
        Vector<long double> x;
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
                x.push_back(stold(token));
            }
            firstLine = false;
            l++;
        }
        file->close();
        return x;
    }

    Vector<String> ReadFile::getAllDataFromColumnString(String columnName)
    {
        if (!mapOfColumns.count(columnName))
        {
            errorMsg("Not a column name", "getAllDataFromColumnString", {columnName});
            return {};
        }
        String text;
        Vector<String> x;
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

    Vector<Vector<String>> ReadFile::getAllRowsWhereColumnIsEqualeToAValue(String columnName, String value)
    {
        if (!mapOfColumns.count(columnName))
        {
            errorMsg("Not a column name", "getAllRowsWhereColumnIsEqualeToAValue", {columnName, value});
            return {{}};
        }
        String text;
        file->open(filename);
        Vector<Vector<String>> x = {};
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

    Vector<String> ReadFile::getRow(int row)
    {
        String text;
        file->open(filename);
        for (int i = 0; i < row + 1; i++)
        {
            getline(*file, text);
        }
        file->close();
        return split(text, splitElement);
    }

    Vector<Vector<String>> ReadFile::getAllData()
    {
        String text;
        file->open(filename);
        Vector<Vector<String>> x = {};
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