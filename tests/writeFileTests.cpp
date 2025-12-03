#include "writeFileTests.hpp"

int main() {
	Vector<int> intTest = { 1, 2, 3, 4 };
	testWriteFile<int>(intTest);

	std::cout << "all tests passed";
}