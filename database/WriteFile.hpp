/*
Athor: Loke Strøm
Created: 12 apr 2022
*/
#pragma once

#include "string.hpp"
#include "Vector.hpp"
#include <fstream>

namespace Database
{
    constexpr char splitElementForDatabase = char(94);

    class WriteFile
    {
    private:
        int columnNumber = 0;
        int dataPointsOnLine = 0;

        void errorMsg(String ErrorMsg, String ErrorFungtion, Vector<String> ErrorFungtionInput)
        {
            String error = "WriteFile: Error: " + ErrorMsg + ". Error was thrown at " + ErrorFungtion + "(";
            if (ErrorFungtionInput.size() != 0)
            {
                for (auto i = 0; i < ErrorFungtionInput.size() - 1; i++)
                    error += "\"" + ErrorFungtionInput[i] + "\", ";
                error += "\"" + ErrorFungtionInput[ErrorFungtionInput.size() - 1] + "\");\n";
            }
            else
                error += "();";
            std::cout << error;
        }

        template <typename T>
        Vector<String> toSVector(Vector<T> v) {
            Vector<String> sv;
            for (const T& i : v)
                sv.pushBack(toS(i));
            return sv;
        }

    public:
        String filename;
        std::ofstream *file = new std::ofstream;
        bool addedData = false;

        //defalt constructor
        WriteFile();
        //constructor opens file
        WriteFile(String filename);
        ~WriteFile();

        void openFile(String filename);

        //add's a column to the file
        void addColumn(String columnName);
        //add's an array of column's to the file
        void addColumnVector(Vector<String> columnNames);

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
        void addDataVector(Vector<T> data)
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