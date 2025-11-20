#include "WriteFile.hpp"
#include "Vector.hpp"
#include "string.hpp"
#include <string>

int main() {
	if (std::filesystem::exists("test.db"))
		std::filesystem::remove("test.db");
	Database::newImplementation::WriteFile<int> test("test.db");

	test.addColumns({ "a", "b", "c" });

	size_t size = 3;
	Database::Vector<int> testi(size, 0);

	for (int i = 0; i < 1000; i++) {
		testi[0] = i * 3 + 1;
		testi[1] = i * 3 + 2;
		testi[2] = i * 3 + 3;
		test.addData(testi);
	}
}