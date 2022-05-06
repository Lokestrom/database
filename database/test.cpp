#include "Vector.hpp"
#include <iostream>
#include <vector>

using namespace Database;

#define Log(x) std::cout << x << "\n"

const void boolcout(bool x) {
	std::string s = (x) ? "true" : "false";
	Log(s);
}

template<typename T>
const void printVector(const Vector<T>& x) {
	for (const T &i : x) {
		std::cout << i << ", ";
	}
	std::cout << "\n";
}

int main()
{
	Vector<int> y;
	y = { 1,2,3,4 };
	Vector<int> x = y;

	printVector(x);

	x.pop(1,3);

	printVector(x);
	Log("x");
}