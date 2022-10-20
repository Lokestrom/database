/*
Athor: Loke Strøm
*/
#include "String.hpp"
#include "Vector.hpp"
#include "Exception.hpp"
#include <fstream>

namespace Database {

	template<typename T>
	WriteFile<T>::WriteFile() {
		file = new ofstream();
		buffer = new Vector<char>();
	}
	template<typename T>
	WriteFile<T>::WriteFile(String file) {
		file = new ofstream(file, std::ios::binary);
		buffer = new Vector<char>();
	}

	template<typename T>
	WriteFile<T>::~WriteFile() {
		delete file;
		delete buffer;
	}

	template<typename T>
	void WriteFile<T>::open(String file) {
		if (file->is_open)
			throw WriteFileError("File is alredy open");
		file->open(file, std::ios::binary);
	}

	template<typename T>
	void WriteFile<T>::addcolumns(Vector<String> columnNames);

	template<typename T>
	void WriteFile<T>::addData(Vector<T> data);
	template<typename T>
	void WriteFile<T>::addData(T data);
}