/*
Athor: Loke Strøm
Created: 12 apr 2022
*/
#pragma once

#include "include.hpp"

using namespace DatabaseFung;

namespace Database
{
    class WriteFile
    {
    private:
        int columnNumber = 0;
        int dataPointsOnLine = 0;
        bool firstLine;
        void errorMsg(const char* ErrorMsg_, const char* ErrorFungtion, std::vector<const char*> ErrorFungtionInput);

    public:
        std::string filename;
        std::ofstream *file = new std::ofstream;
        bool addedData = false;

        //defalt constructor
        WriteFile();
        //constructor opens file
        WriteFile(std::string filename);
        ~WriteFile();

        void openFile(std::string filename);

        //add's a column to the file
        void addColumn(std::string columnName);
        //add's an array of column's to the file
        void addColumnVector(std::vector<std::string> columnNames);

        void addNewLine();

        //Template fungtions:
        template <typename T>
        void addData(T data)
        {
            if (!file->is_open())
            {
                errorMsg("No file is open", "addData", toSVector<T>(data));
                return;
            }
            addedData = true;
            dataPointsOnLine++;
            if (dataPointsOnLine == 1)
            {
                *file << data;
                return;
            }
            *file << "|" << data;
        }

        //add's an array of data to the file. adding data[0] to the first column defined and data[1] to the second...
        template <typename T>
        void addDataVector(std::vector<T> data)
        {
            if (!file->is_open())
            {
                errorMsg("No file is open", "addDataVector", toSVector(data));
                return;
            }
            if (columnNumber > data.size())
            {
                errorMsg("More columns then data, Column count: " + toS(columnNumber) + " Data count: " + toS(data.size()), "addDataVector", toSVector(data));
                return;
            }
            else if (columnNumber < data.size())
            {
                errorMsg("Less columns then data, Column count: " + toS(columnNumber) + " Data count: " + toS(data.size()), "addDataVector", toSVector(data));
                return;
            }
            *file << std::endl;
            addedData = true;
            bool first = true;
            for (T i : data)
            {
                if (!first)
                    *file << "|";
                *file << i;
                first = false;
            }
        }
    };
}