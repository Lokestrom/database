//#include "String.hpp"
#include "Vector.hpp"
#include <unordered_map>
#include <iostream>

using namespace Database;

int main() {

	Vector<int> v = { 1,2,3 }, u = { 1,2,3 };
	std::cout << (v == u);
	//std::unordered_map<String, int> x;
	//String s = "asd";

	//x["hello"] = 3;
	//x[s] = 13;

	//std::cout << x["hello"] << "\t" << x["asd"];
}