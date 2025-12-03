#include "ReadFileTests.hpp"

#include <iostream>

int main() {
	Vector<int> intTest = { 1,2,3,4,5,6,7,8,9,10 };
	testReadFile<int>(intTest);
	
	std::cout << "all tests passed";
}