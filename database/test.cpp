#include "Vector.hpp"
#include <iostream>

using namespace Database;

int main()
{
	Vector<int> x;
	x = { 3,2,1 };

	x.mergeSort();

	std::cout << x[0] << x[1] << x[2];
}