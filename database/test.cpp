#include "String.hpp"
#include "Vector.hpp"
#include <unordered_map>
#include <iostream>

using namespace Database;

int main() {
	std::unordered_map<String, int> x;
	String s = "asd";

	x["hello"] = 3;
	x[s] = 13;

	std::cout << x["hello"] << "\t" << x["asd"];
}