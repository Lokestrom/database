#include "ReadFile.hpp"

#include <iostream>
#include <chrono>

int main() {
	Database::newImplementation::ReadFile<int> file("test.db");
	size_t length = 1E3;

	{
		auto start = std::chrono::high_resolution_clock::now();
		std::array<std::array<int, 3>, 1000> v;
		for (size_t i = 0; i < length; i++)
		{
			file.getAllRows(v);
		}
		auto end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		std::cout << std::setw(20) << duration << "\n";
	}

	{
		auto start = std::chrono::high_resolution_clock::now();
		std::vector<Database::Vector<int>> v;
		for (size_t i = 0; i < length; i++)
		{
			v.clear();
			file.getAllRows(v);
		}
		auto end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		std::cout << std::setw(20) << duration << "\n";
	}
}