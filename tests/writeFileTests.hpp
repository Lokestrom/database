#include "WriteFile.hpp"
#include "Vector.hpp"
#include "string.hpp"
#include <filesystem>
#include <string>
#include <assert.h>

using namespace Database;
using namespace Database::newImplementation;

template<BinarySerializable T>
void testOpeningEmpty() {
	const char* fileName = "testFiles/empty.db";
	WriteFile<T> testFile(fileName);
	assert(std::filesystem::exists(fileName) && "File not created properly");
	assert(testFile.getColumCount() == 0 && "Fault in file creation");
	testFile.close();

	std::ifstream readFile(fileName);
	HeapArray<char> data(4);
	readFile.read(reinterpret_cast<char*>(data.data()), sizeof(unsigned int));
	assert(*reinterpret_cast<unsigned int*>(data.data()) == 0 && "The column count is not written correctly");
	assert(readFile.peek() == EOF && "There has been written more than intended");
	readFile.close();

	testFile.open(fileName);
	assert(testFile.getColumCount() == 0 && "The fault in opening a file with 0 columns");
}

template<BinarySerializable T>
void testWritingColumns() {
	const char* fileName = "testFiles/writeColumns.db";
	WriteFile<T> testFile(fileName);
	assert(std::filesystem::exists(fileName) && "File not created properly");
	assert(testFile.getColumCount() == 0 && "Fault in file creation");
	
	testFile.addColumns({ "a", "b" });
	assert(testFile.getColumCount() == 2 && "Fault in adding columns");
	testFile.close();

	std::ifstream readFile(fileName);
	HeapArray<char> data(8);
	readFile.read(reinterpret_cast<char*>(data.data()), sizeof(data.size()));
	assert(*reinterpret_cast<unsigned int*>(data.data()) == 2 && "The column count is not written correctly");
	String expectedData = String("a") + Database::_splitByte + "b" + Database::_splitByte;
	assert(String(CharSpan(data.data() + 4, expectedData.length())) == expectedData && "The column count is not written correctly");
	assert(readFile.peek() == EOF && "There has been written more than intended");
	readFile.close();

	testFile.open(fileName);
	assert(testFile.getColumCount() == 2 && "Cant read column count correctly");
	testFile.addColumns({ "long column name" });
	assert(testFile.getColumCount() == 3 && "Cant add extra column");
	testFile.addColumns({ "c", "d" });
	assert(testFile.getColumCount() == 5 && "Cant add extra columns correctly");
	testFile.close();

	readFile.open(fileName);
	data = HeapArray<char>(4 + 4 + 18 + 4);
	readFile.read(reinterpret_cast<char*>(data.data()), data.size());
	assert(*reinterpret_cast<unsigned int*>(data.data()) == 5 && "The column count is not written correctly");
	expectedData += String("long column name") + Database::_splitByte + "c" + Database::_splitByte + "d";
	assert(String(CharSpan(data.data() + 4, expectedData.length())) == expectedData && "The names not written correctly");
	assert(readFile.peek() == EOF && "There has been written more than intended");
	readFile.close();
}

template<BinarySerializable T>
void testWritingData(Vector<T> example) {
	Vector<char> dataRow;
	for (auto i = 0; i < 4; i++) {
		const char* bytes = reinterpret_cast<const char*>(&example[i]);
		for (auto j = 0; j < sizeof(T); j++) {
			dataRow.pushBack(bytes[j]);
		}
	}

	const char* fileName = "testFiles/writeData.db";
	WriteFile<T> testFile(fileName);
	assert(std::filesystem::exists(fileName) && "File not created properly");
	assert(testFile.getColumCount() == 0 && "Fault in file creation");

	testFile.addColumns({ "a", "b", "c", "d" });
	Vector<char> expectedData({'a', _splitByte, 'b', _splitByte, 'c', _splitByte, 'd', _splitByte});
	assert(testFile.getColumCount() == 4 && "Fault in adding columns");
	testFile.addData(example);
	expectedData.insert(expectedData.size(), dataRow);
	testFile.close();

	std::ifstream readFile(fileName);
	HeapArray<char> data(4 + 8 + (4 * sizeof(T)));
	readFile.read(reinterpret_cast<char*>(data.data()), data.size());
	assert(*reinterpret_cast<unsigned int*>(data.data()) == 4 && "The column count is not written correctly");
	for (auto i = 0; i < expectedData.size(); i++) {
		if(expectedData[i] != data[i+4])
			assert(false && "The column count is not written correctly");
	}

	assert(readFile.peek() == EOF && "There has been written more than intended");
	readFile.close();

	testFile.open(fileName);
	assert(testFile.getColumCount() == 4 && "Fault in reading columns after adding data");
	testFile.addData(example);
	expectedData.insert(expectedData.size(), dataRow);
	testFile.addData(example);
	expectedData.insert(expectedData.size(), dataRow);
	testFile.addData(example);
	expectedData.insert(expectedData.size() , dataRow);
	testFile.addData(example);
	expectedData.insert(expectedData.size(), dataRow);
	assert(testFile.getColumCount() == 4 && "Column count changed when adding data");
	testFile.close();


	readFile.open(fileName);
	data = HeapArray<char>(4 + 8 + (5 * testFile.getColumCount() * sizeof(T)));
	readFile.read(reinterpret_cast<char*>(data.data()), data.size());
	assert(*reinterpret_cast<unsigned int*>(data.data()) == 4 && "The column count is not written correctly");
	for (auto i = 0; i < expectedData.size(); i++) {
		if (expectedData[i] != data[i + 4])
			assert(false && "The column count is not written correctly");
	}
	assert(readFile.peek() == EOF && "There has been written more than intended");
	readFile.close();
}

template<BinarySerializable T>
void testWriteFile(Vector<T> examples) {
	if (std::filesystem::exists("testFiles"))
		std::filesystem::remove_all("testFiles");
	std::filesystem::create_directory("testFiles");

	testOpeningEmpty<T>();
	testWritingColumns<T>();
	testWritingData<T>(examples);
}
