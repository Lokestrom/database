/*
Athor: Loke Strøm
Created: 13 apr 2022
*/
#include "EditFile.hpp"

namespace Database {
    EditFile::EditFile(std::string filename)
    {
        EditFile::filename = filename;
        ReadFile rF(filename);

        for (const auto& i : rF.mapOfColumns)
            data[i.first] = rF.getAllDataFromColumnString(i.first);

        rF.~ReadFile();
    }

    EditFile::~EditFile()
    {
        WriteFile wF(filename);
        int s = 0;
        for (const auto& i : data)
            if (i.second.size() > s)
                s = i.second.size();

        for (const auto& i : data)
            wF.addColumn(i.first);

        for (auto i = 0; i < s; i++)
            for (const auto& j : data)
                wF.addData(j.second[i]);
    }
}