/*
Athor: Loke Strøm
*/

#include "Exception.hpp"
#include <fstream>

namespace Database {

    template<typename T>
    EditFile<T>::EditFile() {}

    template<typename T>
    EditFile<T>::EditFile(String fileName) {
        _fileName = fileName;
        std::ifstream* file = new std::ifstream(toSTD(fileName));
        unsigned int columnNummber = 0;
        file->read(reinterpret_cast<char*>(&columnNummber), sizeof(unsigned int));
        dataStart = 4;
        String temps;
        char* tempc = new char[1];
        for (int i = 0; i < columnNummber;) {
            file->read(tempc, sizeof(char));
            dataStart++;
            if (tempc[0] == splitByte) {
                ColumnNames.pushBack(temps);
                temps.clear();
                i++;
                continue;
            }
            temps.pushBack(tempc[0]);
        }
        delete file;
    }

    template<typename T>
    void EditFile<T>::open(String fileName) {
        if (_fileName != NULL))
            throw SystemError("A file is alredy open");
        this(fileName);
    }
    template<typename T>
    void EditFile<T>::close() {
        _fileName = NULL;
        columnNames = NULL;
    }


    template<typename T>
    void EditFile<T>::EditCell(T data, String column, size_t row) {
        std::ofstream* file = new std::ofstream(toSTD(_fileName));
        if (columnNames.linearSearch(column) == -1)
            throw InvalidArgument("Column does not exist in file");
        file->seekp(dataStart + (row * sizeof(T) * ColumnNames.size()) + (columnNames.linearSearch(column) * sizeof(T)), std::ios::beg);

        if (file->eof())
            throw InvalidArgument("Row does not exist in file");

        file->write(reinterpret_cast<char*>(&data), sizeof(T));

        delete file;
    }
    template<typename T>
    void EditFile<T>::EditRow(Vector<T> data, size_t row) {
        std::ofstream* file = new std::ofstream(toSTD(_fileName));
        if (data.size() > ColumnNames.size())
            throw InvalidArgument("Column does not exist in file");
        file->seekp(dataStart + (row * sizeof(T) * ColumnNames.size()), std::ios::beg);

        for (const& i : data) {
            if (file->eof())
                throw InvalidArgument("Row does not exist in file");
            file->write(reinterpret_cast<const char*>(&i), sizeof(T));
        }

        delete file;
    }

    template<typename T>
    Vector<size_t> EditFile<T>::SearchInColumn(T data, String column) {
        std::ifstream* file = new std::ifstream(toSTD(_fileName));
        Vector<size_t> rows;
        file->seekg(dataStart + (columnNames.linearSearch(column) * sizeof(T)), std::ios::beg);

        T x;
        for (auto i = 0;; i++) {    
            
            file->read(reinterpret_cast<char*>(&x), sizeof(T));
            if (x = data)
                rows.pushBack(i);
            if (file->eof())
                throw InvalidArgument("Row does not exist in file");
            file->seekg(columnNames.size() * sizeof(T), std::ios::cur);
        }
    }
}