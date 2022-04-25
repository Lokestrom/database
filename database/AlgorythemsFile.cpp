#include "AlgorythemsFile.hpp"

#include "ReadFile.hpp"
#include "WriteFile.hpp"

namespace Database {
    void AlgorythemsFile::mergeSortFileNum(std::string fileName, std::string columnName)
    {
        std::unordered_map<long double, int> x = {};
        std::vector<long double> columnData = {};
        ReadFile rFile(fileName);
        columnData = rFile.getAllDataFromColumnLongDouble(columnName);
        arraySorting::mergeSort(columnData);
        for (int i = 0; i < columnData.size(); i++)
            if (!x.count(columnData[i]))
                x[columnData[i]] = i;

        std::vector<std::vector<std::string>> data = rFile.getAllData();
        std::vector<std::vector<std::string>> sortedData(data.size(), { {""} });

        for (std::vector<std::string> i : data)
            sortedData.insert(sortedData.begin() + x[stold(i[rFile.mapOfColumns[columnName]])], i);

        int j = 0;
        while (j < sortedData.size())
            if (sortedData[j][0] == "")
                sortedData.erase(sortedData.begin() + j);
            else
                j++;

        std::vector<std::string> columnNames = rFile.getRow(0);

        rFile.~ReadFile();

        WriteFile wFile(fileName);
        wFile.addColumnArray(columnNames);
        for (std::vector<std::string> i : sortedData)
            wFile.addDataVector(i);
    }
}