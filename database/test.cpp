#include "Vector.hpp"
#include "String.hpp"
#include <iostream>
using namespace Database;

#define Log(x) std::cout << x

int main()
{
	Vector<int>* x = new Vector<int>();
	x->pushBack(1);
	Vector<int>* y = new Vector<int>(*x);
	x = new Vector<int>({ 1,2,3 });
	int arr[4] = { 4,3,2,1 };
	x = new Vector<int>(arr);

	int z = (*x)[1];
	y = new Vector<int>((*x)(1, 3));

}