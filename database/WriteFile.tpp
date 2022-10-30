/*
Athor: Loke Strøm
*/
#include "String.hpp"
#include "Vector.hpp"
#include "Queue.hpp"
#include "Exception.hpp"
#include <fstream>


namespace Database {

	template<typename T>
	void WriteFile<T>::write() {
		while (!joined || buffer->size() != 0) {
			if (buffer->size() != 0) {
				T val = buffer->pushOff();
				file->write(reinterpret_cast<const char*>(&val), sizeof(char));
			}
		}
	}

	template<typename T>
	WriteFile<T>::WriteFile() {
		file = new std::ofstream();
		buffer = new Queue<char>();
		joined = false;
	}
	template<typename T>
	WriteFile<T>::WriteFile(String filename) {
		file = new std::ofstream(toSTD(filename), std::ios::binary);
		buffer = new Queue<char>();
		tWrite = new std::thread(&WriteFile<T>::write, this);
		joined = false;
	}

	template<typename T>
	WriteFile<T>::~WriteFile() {
		if (file->is_open()) {
			file->close();
			joined = true;
			tWrite->join();
			delete tWrite;
		}
		delete file;
		delete buffer;
	}

	template<typename T>
	void WriteFile<T>::open(String filename) {
		if (file->is_open)
			throw WriteFileError("File is alredy open");
		file->open(filename, std::ios::binary);
		tWrite = new std::thread(&WriteFile<T>::write, this);
	}

	template<typename T>
	void WriteFile<T>::close() {
		if (!file->is_open())
			throw WriteFileError("File is alredy closed");
		joined = true;
		tWrite->join();
		delete tWrite;
		file->close();
	}

	template<typename T>
	void WriteFile<T>::addcolumns(Vector<String> columnNames) {
		for (const auto& i : columnNames) {
			for (const char c : i)
				buffer->pushOn(c);
			buffer->pushOn(splitByte);
		}
	}

	template<typename T>
	void WriteFile<T>::addData(Vector<T> data) {
		for (T i : data) {
			char sizeofdata = sizeof(i);
			char* charRepresentation = (char*)&i;
			for (int j = 0; j < sizeofdata; j++)
				buffer->pushOn(charRepresentation[j]);
		}
	}
}