#include "queueTests.hpp"

#include <iostream>

int main() {
	std::vector<int> intExamples({ 1,2,3,4,5 });
	queueTests<int>(intExamples);
	atomicStaticQueueTests<int>(intExamples);

	std::cout << "all tests passed";
}