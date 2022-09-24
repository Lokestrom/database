/*
Athor: Loke Strøm
Created: 12 apr 2022
*/
#pragma once

#include "string.hpp"
#include "Vector.hpp"
#include "Exception.hpp"
#include <fstream>

namespace Database
{
    constexpr char splitElementForDatabase = char(94);

    class WriteFile
    {
    private:
        int columnNumber = 0;
        int dataPointsOnLine = 0;

        const char* errorMsg(const String ErrorMsg, const String fungtion, const Vector<String> fungtionInput, const Vector<String> fungtionInputType) const noexcept{
            String s;
            s = "WriteFile: Error: " + ErrorMsg + ". Error was thrown at " + fungtion + "( ";
            for (auto i = 0; i < fungtionInputType.size() || i < fungtionInput.size(); i++)
                s += (i > fungtionInputType.size())
                ? "(" + (String)fungtionInputType[i] + "), "
                : "(" + (String)fungtionInputType[i] + ") " + (String)fungtionInput[i] + ", ";

            s.popBack();
            s.popBack();
            s += " );\n";
            return s.data();
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
            *file << splitElementForDatabase << data;
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
            for (const auto& i : data)
            {
                if (!first)
                    *file << splitElementForDatabase;
                *file << i;
                first = false;
            }
        }
    };
}