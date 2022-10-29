#include "Queue.hpp"
#include "String.hpp"
#include <iostream>

using namespace Database;

void a(Vector<int> v) {
	for(int i : v)
		std::cout << i << "\t";
	std::cout << "\n";
}

int main() {
	Queue<Vector<int>> q;
	q.pushOn({1,2});
	q.pushOn({3,4});
	q.pushOn({5,6});
	q.pushOn({7,8});
	a(q.pushOff());
	a(q.pushOff());
	a(q.pushOff());
	a(q.pushOff());
}