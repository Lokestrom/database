#include "Vector.hpp"
#include "String.hpp"
#include <iostream>
#include <vector>

#define Log(x) std::cout << x << "\n";

using namespace Database;

String foo(bool b) {
	return b ? "good, " : "fail, ";
}

void testVector() {
	std::vector<int> stdv = { 1,1,1 };

	//constructors
	Vector<int> v1(stdv);
	Vector<int> v2(v1);
	Vector<int> v3({ 1, 2, 3 });
	Vector<int> v4(7); 
	Vector<int> v5(6, 123);
	
	String x("constructors: ");
	x += foo(v1 == Vector<int>(stdv));
	x += foo(v2 == v1);
	x += foo(v3 == Vector<int>{1, 2, 3});
	x += foo(v4.capacity() == 7);
	x += foo(v5 == Vector<int>{123, 123, 123, 123, 123, 123});
	Log(x);

	v2 = v1;
	v3 = { 3, 2, 1 };

	x = "operator=: ";
	x += foo(v2 == v1);
	x += foo(v3 == Vector<int>{3, 2, 1});
	Log(x);

	v4.clear();
	x = "pushBack: ";
	v4.pushBack(3);
	x += foo(v4[0] = 3);
	Log(x);

	x = "popBack: ";
	v4.popBack();
	x += foo(v4.size() == 0);
	Log(x);

	v1 = { 1,2 };
	v3 = { 3,2,1 };
	x = "insert: ";
	v1.insert(1, 4);
	x += foo(v1 == Vector<int>{ 1,4,2 });
	v1.insert(1, v3);
	x += foo(v1 == Vector<int>{ 1,3,2,1,4,2 });
	v1.insert(1, { 2,3,4 });
	x += foo(v1 == Vector<int>{ 1,2,3,4,3,2,1,4,2 });
	Log(x);

	x = "pop: ";
	v1.pop(4);
	x += foo(v1 == Vector<int>{ 1, 2, 3, 4, 2, 1, 4, 2 });
	v1.pop(1, 3);
	x += foo(v1 == Vector<int>{ 1, 4, 2, 1, 4, 2 });
	Log(x);

	x = "mergeSort: ";
	v1.mergeSort();
	x += foo(v1 == Vector<int>{1, 1, 2, 2, 4, 4});
	Log(x)

	x = "bobbleSort: ";
	v2 = { 4,3,1,7,5,3 };
	v2.bubbleSort();
	x += foo(v2 == Vector<int>{1,3,3,4,5,7});
	Log(x);

	x = "search: ";
	x += foo(v2.binarySerch(5) == 4);
	x += foo(v2.linearSearch(5) == 4);
	Log(x);
}