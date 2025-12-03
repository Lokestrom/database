#include "WriteFile.hpp"
#include "ReadFile.hpp"

#include "Vector.hpp"
using namespace Database;
using namespace Database::newImplementation;

template<BinarySerializable T>
void testOpenEmpty() {
	const char* fileName = "testFiles/Empty.db";
	WriteFile<T> writeFile(fileName);
	writeFile.close();

	ReadFile<T> readFile(fileName);
	assert(readFile.getColumnNames().size() == 0 && "Read Column count incorrectly");
	assert(readFile.columnCount() == 0 && "Read Column count incorrectly");
}

template<BinarySerializable T>
void testSingleRowGetters(Vector<T> examples) {
	assert(examples.size() == 10 && "examples must have 10 elements");
	for (auto i = 0; i < 9; i++)
		for (auto j = i + 1; j < 10; j++)
			assert(examples[i] != examples[j] && "all examples must be unique");

	const char* fileName = "testFiles/singleRows.db";
	WriteFile<T> writeFile(fileName);
	writeFile.addColumns({ "a", "b", "c" });
	writeFile.addData({ examples[0], examples[1], examples[2] });
	writeFile.addData({ examples[0], examples[3], examples[4] });
	writeFile.addData({ examples[0], examples[5], examples[6] });
	writeFile.addData({ examples[9], examples[0], examples[0] });
	writeFile.addData({ examples[0], examples[7], examples[8] });
	writeFile.close();

	ReadFile<T> readFile(fileName);
	Vector<T> dynamicArray(3);
	readFile.getRow(dynamicArray, 1);
	assert(dynamicArray == Vector<T>({ examples[0], examples[3], examples[4] }) && "Not getting correct data");
	dynamicArray.clear();
	readFile.getRow(dynamicArray, 4);
	assert(dynamicArray == Vector<T>({ examples[0], examples[7], examples[8] }) && "Not getting correct data");
	std::function<bool(const Vector<T>&)> condition = [&](Vector<T> row) {
		if (row[1] == examples[5])
			return true;
		return false;
		};
	assert(readFile.getRow(dynamicArray, condition) && "Conditional row getter failed");
	assert(dynamicArray == Vector<T>({ examples[0], examples[5], examples[6] }) && "Conditional row getter failed");

	HeapArray<T> staticArray(3);
	readFile.getRow(staticArray, 0);
	assert(staticArray == Vector<T>({ examples[0], examples[1], examples[2] }) && "Not getting correct data");
	readFile.getRow(staticArray, 3);
	assert(staticArray == Vector<T>({ examples[9], examples[0], examples[0] }) && "Not getting correct data");
}

template<BinarySerializable T>
void testReadFile(Vector<T> examples) {
	if (std::filesystem::exists("testFiles"))
		std::filesystem::remove_all("testFiles");
	std::filesystem::create_directory("testFiles");
	testOpenEmpty<T>();
	testSingleRowGetters<T>(examples);
}