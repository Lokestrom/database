/*
Athor: Loke Strøm
Created: 12 apr 2022
*/
#pragma once

#include "WriteFile.hpp"

namespace Database
{
    //used to read a file in the database
    class ReadFile
    {
    private:
        int nextColumnNumber = 0;
        std::ifstream *file = new std::ifstream;
        bool firstLine;

        void errorMsg(std::string ErrorMsg_, std::string ErrorFungtion, std::vector<std::string> ErrorFungtionInput);

    public:
        std::unordered_map<std::string, int> mapOfColumns = {};
        std::string filename;

        //constructer
        ReadFile(std::string fileName);
        ~ReadFile();

        //double version for graff thing
        std::vector<double> getAllDataFromColumnDouble(std::string columnName);
        //long double version for all other stuff
        std::vector<long double> getAllDataFromColumnLongDouble(std::string columnName);
        std::vector<std::string> getAllDataFromColumnString(std::string columnName);
        std::vector<std::vector<std::string>> getAllRowsWhereColumnIsEqualeToAValue(std::string columnName, std::string value);
        std::vector<std::string> getRow(int row);
        std::vector<std::vector<std::string>> getAllData();
    };
}