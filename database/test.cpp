#include "Vector.hpp"
#include <iostream>

using namespace Database;

int main()
{
	Vector<int> vec;
	vec.pushBack(2);
	std::cout << vec[0];
}