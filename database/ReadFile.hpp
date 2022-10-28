/*
Athor: Loke Strøm
*/
#pragma once

#include "WriteFile.hpp"

#include <unordered_map>

namespace Database
{
    //used to read a file in the database
    class ReadFile
    {
    private:
        int nextColumnNumber = 0;
        std::ifstream *file = new std::ifstream;
        bool firstLine;

    public:
        std::unordered_map<String, int> mapOfColumns;
        String filename;

        //constructer
        ReadFile(String fileName);
        ~ReadFile();

        //double version for graff thing
        Vector<double> getAllDataFromColumnDouble(String columnName);
        //long double version for all other stuff
        Vector<long double> getAllDataFromColumnLongDouble(String columnName);
        Vector<String> getAllDataFromColumnString(String columnName);
        Vector<Vector<String>> getAllRowsWhereColumnIsEqualeToAValue(String columnName, String value);
        Vector<String> getRow(int row);
        Vector<Vector<String>> getAllData();
    };
}