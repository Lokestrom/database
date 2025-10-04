#include "String.hpp"
#include <cassert>
#include <iostream>

using namespace Database;

void testPushBack() {
	String str;
	str.pushBack('H');
	str.pushBack('i');
	assert(str.length() == 2);
	assert(str[0] == 'H');
	assert(str[1] == 'i');
}

int main() {
	testPushBack();
	std::cout << "All tests passed!" << std::endl;
	return 0;
}