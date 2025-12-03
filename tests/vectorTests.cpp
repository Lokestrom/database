#include "vectorTests.hpp"

#if DATABASE_EXCEPTIONS_ENABLED == 0
#error tests must be compiled with exceptions
#endif

int main() {
	int intExamples[5] = { 1, 10, 42, 500, 7000 };
	runTests(intExamples);

	std::cout << "All tests passed!" << std::endl;
    return 0;
}