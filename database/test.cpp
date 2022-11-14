#include "WriteFile.hpp"
#include "ReadFile.hpp"
#include <chrono>
#include <iostream>
using namespace Database;

int main() {
	unsigned int runTimes = 1E7;
	String file = "a.db";

	{
		//auto start = std::chrono::steady_clock::now();
		WriteFile<double> w(file);

		w.addcolumns({ "a", "b", "c", "de" });
		w.addData({ 1,2,3,4 });
		w.addData({ 2,2,3,4 });
		w.addData({ 3,3,3,4 });
		w.close();
		//auto end = std::chrono::steady_clock::now();
		//std::cout << "write: " << std::chrono::duration <double, std::milli >(end - start).count() << " ms\n";
	}

	{
		//auto start = std::chrono::steady_clock::now();
		ReadFile<double> r(file);
		Vector<double> v;
		r.getAllDataFromColumn(v, "b");
		for (const auto& i : v) {
			std::cout << i << "\t";
		}
		//auto end = std::chrono::steady_clock::now();
		//std::cout << "Read: " << std::chrono::duration <double, std::milli >(end - start).count() << " ms\n";
	}
}