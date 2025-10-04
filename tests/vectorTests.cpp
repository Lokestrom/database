#include "Vector.hpp"
#include "Exception.hpp"
#include <cassert>
#include <iostream>

using namespace Database;

void testPushBack() {
    Vector<int> vec;
    vec.pushBack(10);
    vec.pushBack(20);
    assert(vec.size() == 2);
    assert(vec[0] == 10);
    assert(vec[1] == 20);
}

void testAt() {
    Vector<int> vec;
    vec.pushBack(10);
    vec.pushBack(20);
    try {
        vec.at(2);
        assert(false);
    } catch (const OutOfRange&) {
        assert(true);
    }
}

int main() {
    testPushBack();
	testAt();

	std::cout << "All tests passed!" << std::endl;
    return 0;
}