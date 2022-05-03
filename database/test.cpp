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
	Vector<int> x = {1,2,3,4}, y = {1,2,3};

	x.insert(0, 1);

	printVector(x);
}