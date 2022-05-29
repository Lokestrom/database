#include "Vector.hpp"
#include <iostream>

#define Log(x) std::cout << x << "\n";

using namespace Database;

int main() {
	//ekstras
	Vector<int> test({ 1,2,3 });

	//constructors
	Vector<int> v1 = { 1,1,1 };
	Vector<int> v2(test);
	Vector<int> v3({ 1, 2, 3 });
	Vector<int> v4(7);
	v1.printVectorData();
	v2.printVectorData();
	v3.printVectorData();
	v4.printVectorData();

	Log(v3[4]);
	v2 = test(0, 2);
	v2.printVectorData();

	v2 = { 1,2,3,4 };
	v2.printVectorData();

	std::string x;
	if (test == v3)
		x += "y    ";
	if (test == v2)
		x += "n    ";
	if (test != v2)
		x += "y    ";
	if (test != v3)
		x += "n    ";

	Log(x);

	Log(v1.empty());
	v1.clear();
	v1.printVectorData();
	Log(v1.empty());

	v2.printVectorData();
	Log(v2.size());
	Log(v2.capacity());
	v2.reserve(100);
	Log(v2.capacity());
	v2.shrinkToFit();
	v2.printVectorData();
	Log(v2.capacity());

	int* vecdata = v2.data();

	for (int& i : v3)
		Log(i);
	for (const int& i : v3)
		Log(i);

	v4.pushBack(3);
	v4.printVectorData();
	v4.popBack();
	v4.printVectorData();

	v4 = { 8,4,2,3,5,7,4,2 };
	v1 = {1};

	v1.insert(1, 4);
	v1.printVectorData();
	v1.insert(1, v4);
	v1.printVectorData();
	v1.insert(1, { 2,3,4 });
	v1.printVectorData();

	v1.pop(4);
	v1.printVectorData();
	v1.pop(1, 3);
	v1.printVectorData();

	v1.mergeSort();
	v1.printVectorData();
	
	v2 = { 4,3,1,7,5,3 };
	v2.bubbleSort();
	v2.printVectorData();

	Log(v2.binarySerch(5));
	Log(v2.linearSearch(5));
}