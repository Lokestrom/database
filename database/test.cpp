#include "WriteFile.hpp"
using namespace Database;

int main() {
	WriteFile<int> w("text.bin");

	w.addcolumns({ "a", "b", "c" });
	w.addData({ 11,12,13 });
	w.close();
}