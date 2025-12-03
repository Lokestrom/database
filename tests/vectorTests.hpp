#include "Vector.hpp"
#include <cassert>
#include <iostream>

using namespace Database;

template<TrivialElement T>
void checkVector(const Vector<T>& v, const std::initializer_list<T>& expected) {
	assert(v.size() == expected.size() && "Vector size does not match expected size");
	assert(v.capacity() >= v.size() && "Vector capacity is less than the size");
	for (size_t i = 0; i < v.size(); i++) {
		assert(v[i] == expected.begin()[i] && "Vector element does not match expected element");
	}
}

template<TrivialElement T>
void testConstructor(T* examples) {
	Vector<T> vecDefault;
	checkVector(vecDefault, {});
	assert(vecDefault.capacity() == 0 && "Default constructor must not allocate memory");
	assert(vecDefault.data() == nullptr && "Default constructor must not allocate memory");
	vecDefault.pushBack(examples[1]);
	vecDefault.pushBack(examples[4]);
	vecDefault.pushBack(examples[2]);

	Vector<T> vectorCopy = vecDefault;
	checkVector(vectorCopy, { examples[1], examples[4], examples[2] });
	Vector<T> vectorMove(vectorCopy);
	checkVector(vectorMove, { examples[1], examples[4], examples[2] });

	Vector<T> vecInitializer_list({ examples[2], examples[2], examples[3], examples[0], examples[0] });
	checkVector(vecInitializer_list, { examples[2], examples[2], examples[3], examples[0], examples[0] });
	std::vector<T> stdVector = { examples[3], examples[0], examples[1] };
	Vector<T> vecStd(stdVector);
	checkVector(vecStd, { examples[3], examples[0], examples[1] });
	
	Vector<T> vecCapacity(5);
	assert(vecCapacity.capacity() == 5 && "Capacity incorrectly set");
	checkVector(vecCapacity, {});

	Vector<T> vecFill(3, examples[4]);
	checkVector(vecFill, { examples[4], examples[4], examples[4] });
}

template<TrivialElement T>
void testAssignment(T* examples) {
	Vector<T> vec({ examples[0], examples[1] });
	checkVector(vec, { examples[0], examples[1] });

	Vector<T> vecCopy;
	vecCopy = vec;
	checkVector(vecCopy, { examples[0], examples[1] });
	
	Vector<T> vecMove;
	vecMove = std::move(vec);
	checkVector(vecMove, { examples[0], examples[1] });

	Vector<T> vecInitializer_list;
	vecInitializer_list = { examples[4], examples[2], examples[0] };
	checkVector(vecInitializer_list, { examples[4], examples[2], examples[0] });

	vecMove += vecMove;
	checkVector(vecMove, { examples[0], examples[1], examples[0], examples[1] });
}

template<TrivialElement T>
void testInsert(T* examples) {
	Vector<T> vec;
	vec.pushBack(examples[0]);
	vec.pushBack(examples[0]);
	checkVector(vec, { examples[0], examples[0] });

	vec.insert(0, examples[4]);
	vec.insert(3, examples[3]);
	checkVector(vec, { examples[4], examples[0], examples[0], examples[3] });

	vec.insert(2, { examples[2], examples[1] });
	checkVector(vec, { examples[4], examples[0], examples[2], examples[1], examples[0], examples[3]});

	vec.insert(4, vec);
	checkVector(vec, { examples[4], examples[0], examples[2], examples[1], examples[4],
		examples[0], examples[2], examples[1], examples[0], examples[3], examples[0], examples[3] });
}

template<TrivialElement T>
void testPop(T* examples) {
	Vector<T> vec = { examples[0], examples[0], examples[4], examples[3], examples[0],
		examples[0], examples[4], examples[3], examples[2], examples[1], examples[2], examples[1] };

	vec.popBack();
	vec.popBack();
	checkVector(vec, { examples[0], examples[0], examples[4], examples[3], examples[0],
		examples[0], examples[4], examples[3], examples[2], examples[1] });
	vec.pop(0);
	vec.pop(2);
	vec.pop(7);
	checkVector(vec, { examples[0], examples[4], examples[0],
		examples[0], examples[4], examples[3], examples[2] });

	vec.pop(2, 5);
	checkVector(vec, { examples[0], examples[4], examples[3], examples[2] });
}

template<TrivialElement T>
void testSort(T* sortedExamples) {
	Vector<T> merge = { sortedExamples[2], sortedExamples[2], sortedExamples[0], sortedExamples[4] };
	merge.mergeSort();
	checkVector(merge, { sortedExamples[0], sortedExamples[2], sortedExamples[2], sortedExamples[4] });
	Vector<T> bubble = { sortedExamples[3], sortedExamples[2], sortedExamples[4], sortedExamples[0] };
	bubble.bubbleSort();
	checkVector(bubble, { sortedExamples[0], sortedExamples[2], sortedExamples[3], sortedExamples[4] });
}

template<TrivialElement T>
void testSearch(T* sortedExamples) {
	Vector<T> vec = { sortedExamples[0], sortedExamples[1], sortedExamples[2], sortedExamples[2], sortedExamples[4], sortedExamples[4] };
	assert((vec.binarySearch(sortedExamples[2]) == 2 || vec.binarySearch(sortedExamples[2]) == 3) && "Binary search fail");
	assert(vec.linearSearch(sortedExamples[1]) == 1 && "linear search fail");
	assert(vec.linearSearchR(sortedExamples[4]) == 5 && "linear search reverse fail");

	assert(vec.binarySearch(sortedExamples[3]) == 6 && "binary search fail");
	assert(vec.linearSearch(sortedExamples[3]) == 6 && "linear search fail");
}

template<TrivialElement T>
void testCapasityModifiers(T* examples) {
	Vector<T> vec;
	vec.reserve(5);
	assert(vec.capacity() == 5 && "capacity reserved incorrectly");
	checkVector(vec, {});
	
	vec = { examples[1], examples[3], examples[2] };
	vec.shrinkToFit();
	assert(vec.capacity() == 3 && "capacity not shrunk correctly");
	checkVector(vec, { examples[1], examples[3], examples[2] });
}

template<TrivialElement T>
void runTests(T* examples) {
	testConstructor(examples);
	testAssignment(examples);
	testInsert(examples);
	testPop(examples);
	testSort(examples);
	testSearch(examples);
	testCapasityModifiers(examples);
}