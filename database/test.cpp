#include "Vector.hpp"
#include <iostream>

using namespace Database;

#define Log(x) std::cout << x << "\n"

const void boolcout(bool x) {
	std::string s = (x) ? "true" : "false";
	Log(s);
}

template<typename T>
const void printVector(Vector<T>& x) {
	std::cout << x[0];
	for (int i = 1; i < x.size(); i++) {
		std::cout << ", " << x[i];
	}
	std::cout << "\n";
}

int main()
{
	Vector<int> x;

	x.pushBack(1);
	x.pushBack(2);
	printVector(x);

	x.pop(0);

	printVector(x);
}