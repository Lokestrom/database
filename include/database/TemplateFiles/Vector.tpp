/*
Author: Loke Strøm
*/
#include <initializer_list>
#include <utility>
#include <ranges>
#include <algorithm>

#include "Vector.hpp"

namespace Database
{

template <TrivialElement T>
Vector<T>::Vector() noexcept {
	_currentCapacity = 0;
	_currentSize = 0;
}

template <TrivialElement T>
Vector<T>::Vector(const Vector<T>& vector) {
	DATABASE_EXCEPTION_HANDLING_IF_EXPECTED_ERROR_THROW(newArray(vector.data(), vector.size()));
}
template <TrivialElement T>
Vector<T>::Vector(Vector<T>&& vector) noexcept {
	this->_arr = vector._arr;
	this->_currentSize = vector._currentSize;
	this->_currentCapacity = vector._currentCapacity;
	vector._arr = nullptr;
}

template <TrivialElement T>
Vector<T>::Vector(const std::initializer_list<T>& initializerList) {
	*this = initializerList;
}

template <TrivialElement T>
Vector<T>::Vector(const std::vector<T>& vector) {
	DATABASE_EXCEPTION_HANDLING_IF_EXPECTED_ERROR_THROW(newArray(vector.data(), vector.size()));
}

template <TrivialElement T>
Vector<T>::Vector(const size_t capacity) {
	DATABASE_EXCEPTION_HANDLING_IF_EXPECTED_ERROR_THROW(allocateNewArray(capacity));
}

template <TrivialElement T>
Vector<T>::Vector(const size_t count, const T& value) {
	DATABASE_EXCEPTION_HANDLING_IF_EXPECTED_ERROR_THROW(allocateNewArray(count));
	std::fill(_arr, _arr + _currentCapacity, value);
	_currentSize = count;
}

template <TrivialElement T>
Vector<T>::~Vector() noexcept {
	delete[] _arr;
}

template <TrivialElement T>
T& Vector<T>::operator[] (const size_t index) noexcept {
	return _arr[index];
}

template <TrivialElement T>
const T& Vector<T>::operator[] (const size_t index) const noexcept {
	return _arr[index];
}

template <TrivialElement T>
Expected<Vector<T>> Vector<T>::operator() (const size_t startIndex, const size_t endIndex) const DATABASE_EXCEPTION_HANDLING_NOEXCEPT {
	if (endIndex > _currentSize)
		DATABASE_EXCEPTION_HANDLING_THROW_ERROR("endIndex out of range");
	if (startIndex > endIndex)
		DATABASE_EXCEPTION_HANDLING_THROW_ERROR("startIndex can't be greater than endIndex");

#if DATABASE_EXCEPTIONS_ENABLED == 1
	Vector<T> x(endIndex - startIndex);
#else
	Vector<T> x;
	PROPEGATE_ERROR(x.reserve(endIndex - startIndex));
#endif
	x.copyArray(begin() + startIndex, endIndex - startIndex);
	return x;
}

template <TrivialElement T>
Vector<T>& Vector<T>::operator= (const Vector<T>& x) {
	DATABASE_EXCEPTION_HANDLING_IF_EXPECTED_ERROR_THROW(newArray(x.data(), x.size()));
	return *this;
}

template<TrivialElement T>
Vector<T>& Vector<T>::operator= (Vector<T>&& vector) noexcept {
	this->_arr = vector._arr;
	this->_currentSize = vector._currentSize;
	this->_currentCapacity = vector._currentCapacity;
	vector._arr = nullptr;
	return *this;
}

template <TrivialElement T>
Vector<T>& Vector<T>::operator= (const std::initializer_list<T> initializerList) {
	DATABASE_EXCEPTION_HANDLING_IF_EXPECTED_ERROR_THROW(newArray(initializerList.begin(), initializerList.size()));
	return *this;
}

template <TrivialElement T>
Vector<T>& Vector<T>::operator+= (const Vector<T>& vector) {
	DATABASE_EXCEPTION_HANDLING_IF_EXPECTED_ERROR_THROW(resizeIfNeeded(_currentSize + vector.size()));
	std::memcpy(_arr + _currentSize, vector.data(), vector.size() * sizeof(T));
	_currentSize += vector.size();
	return *this;
}

template <TrivialElement T>
Expected<T&> Vector<T>::at(const size_t index) DATABASE_EXCEPTION_HANDLING_NOEXCEPT {
	if (index >= _currentSize)
		DATABASE_EXCEPTION_HANDLING_THROW_ERROR("Index out of range");
	return _arr[index];
}

template <TrivialElement T>
Expected<const T&> Vector<T>::at(const size_t index) const DATABASE_EXCEPTION_HANDLING_NOEXCEPT {
	if (index >= _currentSize)
		DATABASE_EXCEPTION_HANDLING_THROW_ERROR("Index out of range");
	return _arr[index];
}

template<TrivialElement T>
bool Vector<T>::empty() const noexcept {
	return _currentSize == 0;
}

template<TrivialElement T>
size_t Vector<T>::size() const noexcept {
	return _currentSize;
}

template<TrivialElement T>
void Vector<T>::clear() noexcept {
	_currentSize = 0;
}

template<TrivialElement T>
size_t Vector<T>::capacity() const noexcept {
	return _currentCapacity;
}

template<TrivialElement T>
Expected<void> Vector<T>::shrinkToFit() DATABASE_EXCEPTION_HANDLING_NOEXCEPT {
	DATABASE_EXCEPTION_HANDLING_PROPEGATE_ERROR(resizeArray(_currentSize));
}

template<TrivialElement T>
Expected<void> Vector<T>::reserve(const size_t newCapacity) DATABASE_EXCEPTION_HANDLING_NOEXCEPT {
	if (newCapacity == _currentCapacity) {
		return;
	}
	if (newCapacity < _currentCapacity) {
		DATABASE_EXCEPTION_HANDLING_THROW_ERROR("newCapacity can't be less than currentCapacity");
	}
	DATABASE_EXCEPTION_HANDLING_PROPEGATE_ERROR(resizeArray(newCapacity));
}

template<TrivialElement T>
T* Vector<T>::data() noexcept {
	return _arr;
}

template<TrivialElement T>
const T* Vector<T>::data() const noexcept {
	return _arr;
}

template<TrivialElement T>
T* Vector<T>::begin() noexcept {
	return _arr;
}

template<TrivialElement T>
T* Vector<T>::end() noexcept {
	return _arr + _currentSize;
}

template<TrivialElement T>
const T* Vector<T>::begin() const noexcept {
	return _arr;
}

template<TrivialElement T>
const T* Vector<T>::end() const noexcept {
	return  _arr + _currentSize;
}

template<TrivialElement T>
Expected<void> Vector<T>::pushBack(const T& val) DATABASE_EXCEPTION_HANDLING_NOEXCEPT {
	DATABASE_EXCEPTION_HANDLING_PROPEGATE_ERROR(resizeIfNeeded(_currentSize + 1));
	_arr[_currentSize] = val;
	_currentSize++;
}

template<TrivialElement T>
Expected<void> Vector<T>::popBack() DATABASE_EXCEPTION_HANDLING_NOEXCEPT {
	if (_currentSize == 0)
		DATABASE_EXCEPTION_HANDLING_THROW_ERROR("Can't popBack on empty Vector");
	_currentSize--;
}

template<TrivialElement T>
Expected<void> Vector<T>::insert(const size_t index, T val) DATABASE_EXCEPTION_HANDLING_NOEXCEPT {
	if (index > _currentSize)
		DATABASE_EXCEPTION_HANDLING_THROW_ERROR("Index out of range");

	DATABASE_EXCEPTION_HANDLING_PROPEGATE_ERROR(resizeIfNeeded(_currentSize + 1));
	std::memmove(&_arr[index + 1], &_arr[index], (_currentSize - index) * sizeof(T));
	_arr[index] = val;
	_currentSize++;
}

template<TrivialElement T>
Expected<void> Vector<T>::insert(const size_t index, const Vector<T>& vector) DATABASE_EXCEPTION_HANDLING_NOEXCEPT {
	if (index > _currentSize)
		DATABASE_EXCEPTION_HANDLING_THROW_ERROR("Index out of range");
	DATABASE_EXCEPTION_HANDLING_PROPEGATE_ERROR(resizeIfNeeded(_currentSize + vector.size()));
	std::memmove(&_arr[index + vector.size()], &_arr[index], (_currentSize - index) * sizeof(T));
	std::memcpy(&_arr[index], vector.data(), (vector.size()) * sizeof(T));
	_currentSize += vector.size();
}


template<TrivialElement T>
Expected<void> Vector<T>::insert(const size_t index, const std::initializer_list<T> initializerList) DATABASE_EXCEPTION_HANDLING_NOEXCEPT {
	if (index > _currentSize)
		DATABASE_EXCEPTION_HANDLING_THROW_ERROR("Index out of range");
	DATABASE_EXCEPTION_HANDLING_PROPEGATE_ERROR(resizeIfNeeded(_currentSize + initializerList.size()));
	std::memmove(&_arr[index + initializerList.size()], &_arr[index], (_currentSize - index) * sizeof(T));
	std::memcpy(&_arr[index], initializerList.begin(), (initializerList.size()) * sizeof(T));
	_currentSize += initializerList.size();
}

template<TrivialElement T>
Expected<void> Vector<T>::pop(const size_t index) DATABASE_EXCEPTION_HANDLING_NOEXCEPT {
	if (index >= _currentSize)
		DATABASE_EXCEPTION_HANDLING_THROW_ERROR("Index out of range");
	std::memmove(&_arr[index], &_arr[index + 1], (_currentSize - index) * sizeof(T));
	_currentSize--;
}

template<TrivialElement T>
Expected<void> Vector<T>::pop(const size_t startIndex, const size_t endIndex) DATABASE_EXCEPTION_HANDLING_NOEXCEPT {
	if (endIndex > _currentSize)
		DATABASE_EXCEPTION_HANDLING_THROW_ERROR("endIndex out of range");
	if (startIndex > endIndex)
		DATABASE_EXCEPTION_HANDLING_THROW_ERROR("startIndex can't be greater than endIndex");

	std::memmove(&_arr[startIndex], &_arr[endIndex], (_currentSize - endIndex) * sizeof(T));
	_currentSize -= endIndex - startIndex;
}


template<TrivialElement T>
Expected<void> Vector<T>::mergeSort() DATABASE_EXCEPTION_HANDLING_NOEXCEPT {
	static_assert(std::totally_ordered<T> && "Type must be totally ordered");
	if (this->size() == 1)
		return;
	DATABASE_EXCEPTION_HANDLING_HANDLE_EXCEPTION_BEGIN
	Vector<T> start;
	DATABASE_EXCEPTION_HANDLING_TRY_ASSIGN(start, this->operator()(0, this->size() / 2));
	Vector<T> end;
	DATABASE_EXCEPTION_HANDLING_TRY_ASSIGN(end, this->operator()(this->size() / 2, this->size()));

	DATABASE_EXCEPTION_HANDLING_PROPEGATE_ERROR(start.mergeSort());
	DATABASE_EXCEPTION_HANDLING_PROPEGATE_ERROR(end.mergeSort());

	clear();

	size_t startPos = 0, endPos = 0;

	while (startPos != start.size() && endPos != end.size()) {
		if (start[startPos] < end[endPos]) {
			DATABASE_EXCEPTION_HANDLING_SAFE_GARANTEE(pushBack(start[startPos]));
			startPos++;
		}
		else {
			DATABASE_EXCEPTION_HANDLING_SAFE_GARANTEE(pushBack(end[endPos]));
			endPos++;
		}
	}

	for (; startPos != start.size(); startPos++)
		DATABASE_EXCEPTION_HANDLING_SAFE_GARANTEE(pushBack(start[startPos]));
	for (; endPos != end.size(); endPos++)
		DATABASE_EXCEPTION_HANDLING_SAFE_GARANTEE(pushBack(end[endPos]));
	DATABASE_EXCEPTION_HANDLING_HANDLE_EXCEPTION_END
}

template<TrivialElement T>
void Vector<T>::bubbleSort() noexcept {
	static_assert(std::totally_ordered<T> && "Type must be totally ordered");
	T temp;
	for (auto i = 0; i < _currentSize; i++) {
		for (auto j = 0; j < _currentSize - i - 1; j++) {
			if (_arr[j] > _arr[j + 1]) {
				temp = _arr[j + 1];
				_arr[j + 1] = _arr[j];
				_arr[j] = temp;
			}
		}
	}
}

template<TrivialElement T>
size_t Vector<T>::binarySearch(const T target) const noexcept {
	static_assert(std::totally_ordered<T> && "Type must be totally ordered");
	assert(std::ranges::is_sorted(*this) && "Vector must be sorted");
	size_t low = 0;
	size_t high = _currentSize - 1;
	size_t mid;

	while (low <= high) {
		mid = (low + high) / 2;

		if (_arr[mid] == target)
			return mid;
		else if (_arr[mid] > target)
			high = mid - 1;
		else
			low = mid + 1;
	}
	return _currentSize;
}

template<TrivialElement T>
size_t Vector<T>::linearSearch(const T target) const noexcept {
	static_assert(std::equality_comparable<T> && "Type must be equality comparable");
	for (auto i = 0; i < _currentSize; i++)
		if (_arr[i] == target)
			return i;
	return _currentSize;
}

template<TrivialElement T>
size_t Vector<T>::linearSearchR(const T target) const noexcept {
	static_assert(std::equality_comparable<T> && "Type must be equality comparable");
	size_t i = _currentSize;
	do {
		i--;
		if (_arr[i] == target)
			return i;
	} while (i != 0);
	return _currentSize;
}

template<TrivialElement T>
void Vector<T>::copyArray(const T* s, size_t len) noexcept {
	std::memcpy(_arr, s, len * sizeof(T));
	_currentSize = len;
}

template<TrivialElement T>
Expected<void> Vector<T>::allocateNewArray(size_t newCapacity) DATABASE_EXCEPTION_HANDLING_NOEXCEPT {
	delete[] _arr;
	DATABASE_EXCEPTION_HANDLING_HANDLE_EXCEPTION_BEGIN
	_arr = new T[newCapacity];
	DATABASE_EXCEPTION_HANDLING_HANDLE_EXCEPTION_END
	_currentCapacity = newCapacity;
}

template<TrivialElement T>
Expected<void> Vector<T>::newArray(const T* s, size_t len) DATABASE_EXCEPTION_HANDLING_NOEXCEPT {
	DATABASE_EXCEPTION_HANDLING_PROPEGATE_ERROR(allocateNewArray(len));
	copyArray(s, len);
}

template<TrivialElement T>
Expected<void> Vector<T>::resizeArray(size_t newCapacity) DATABASE_EXCEPTION_HANDLING_NOEXCEPT {
	DATABASE_EXCEPTION_HANDLING_HANDLE_EXCEPTION_BEGIN
	T* temp = new T[newCapacity];
	std::memcpy(temp, _arr, _currentSize * sizeof(T));
	delete[] _arr;
	_arr = temp;
	DATABASE_EXCEPTION_HANDLING_HANDLE_EXCEPTION_END
	_currentCapacity = newCapacity;
}

template<TrivialElement T>
Expected<void> Vector<T>::resizeIfNeeded(size_t newExpectedSize) DATABASE_EXCEPTION_HANDLING_NOEXCEPT {
	if (newExpectedSize > _currentCapacity) {
		size_t newCap = newExpectedSize + (newExpectedSize / 2) + 2;
		DATABASE_EXCEPTION_HANDLING_PROPEGATE_ERROR(resizeArray(newCap));
	}
}

}

namespace Database
{
template<TrivialElement T>
HeapArray<T>::HeapArray(size_t size)
	: _size(size), _arr(new T[size])
{
}
template<TrivialElement T>
HeapArray<T>::HeapArray(T* data, size_t size) 
	: _size(size), _arr(new T[size])
{
	std::copy(data, data + size, _arr);
}

template<TrivialElement T>
HeapArray<T>::HeapArray(const T& value, size_t size) 
	: _size(size), _arr(new T[size])
{
	std::fill_n(_arr, _size, value);
}

template<TrivialElement T>
HeapArray<T>::~HeapArray() noexcept {
	delete[] _arr;
}

template<TrivialElement T>
HeapArray<T>::HeapArray(const HeapArray& other) 
	: _size(other.size()), _arr(new T[other.size()])
{
	std::copy(other.data(), other.data() + other.size(), _arr);
}

template<TrivialElement T>
HeapArray<T>::HeapArray(HeapArray&& other) noexcept
	: _size(other._size), _arr(other._arr) {
	other._arr = nullptr;
	other._size = 0;
}
template<TrivialElement T>
HeapArray<T>& HeapArray<T>::operator=(HeapArray<T>&& other) noexcept {
	if (this != &other) {
		delete[] _arr;
		_arr = other._arr;
		_size = other._size;
		other._arr = nullptr;
		other._size = 0;
	}
	return *this;

}

template<TrivialElement T>
HeapArray<T>& HeapArray<T>::operator=(const HeapArray& other) {
	if (this == &other)
		return *this;

	delete[] _arr;
	_arr = new T[other._size];
	_size = other._size;
	std::copy(other._arr, other._arr + other._size, _arr);
	return *this;
}

template<TrivialElement T>
T& HeapArray<T>::operator[](size_t index) noexcept {
	return _arr[index];
}
template<TrivialElement T>
const T& HeapArray<T>::operator[](size_t index) const noexcept {
	return _arr[index];
}
template<TrivialElement T>
T* HeapArray<T>::begin() noexcept {
	return _arr;
}
template<TrivialElement T>
const T* HeapArray<T>::begin() const noexcept {
	return _arr;
}
template<TrivialElement T>
T* HeapArray<T>::end() noexcept {
	return _arr + _size;
}
template<TrivialElement T>
const T* HeapArray<T>::end() const noexcept {
	return _arr + _size;
}
template<TrivialElement T>
size_t HeapArray<T>::size() const noexcept {
	return _size;
}
template<TrivialElement T>
T* HeapArray<T>::data() noexcept {
	return _arr;
}
template<TrivialElement T>
const T* HeapArray<T>::data() const noexcept {
	return _arr;
}
}

namespace Database
{
template <TrivialElement T>
bool operator==(const Vector<T>& lhs, const Vector<T>& rhs) noexcept {
	static_assert(std::equality_comparable<T> && "Type must be totally ordered");
	if (lhs.size() != rhs.size())
		return false;

	return memcmp(lhs.data(), rhs.data(), lhs.size() * sizeof(T)) == 0;
}

template <TrivialElement T>
bool operator!=(const Vector<T>& lhs, const Vector<T>& rhs) noexcept {
	static_assert(std::equality_comparable<T> && "Type must be totally ordered");
	return !(lhs == rhs);
}
template <TrivialElement T>
bool operator== (const HeapArray<T>& lhs, const HeapArray<T>& rhs) noexcept {
	static_assert(std::equality_comparable<T> && "Type must be totally ordered");
	if (lhs.size() != rhs.size())
		return false;

	return memcmp(lhs.data(), rhs.data(), lhs.size() * sizeof(T)) == 0;
}
template <TrivialElement T>
bool operator!= (const HeapArray<T>& lhs, const HeapArray<T>& rhs) noexcept {
	return !(lhs == rhs);
}
template <TrivialElement T>
bool operator== (const HeapArray<T>& lhs, const Vector<T>& rhs) noexcept {
	static_assert(std::equality_comparable<T> && "Type must be totally ordered");
	if (lhs.size() != rhs.size())
		return false;

	return memcmp(lhs.data(), rhs.data(), lhs.size() * sizeof(T)) == 0;
}
template <TrivialElement T>
bool operator!= (const HeapArray<T>& lhs, const Vector<T>& rhs) noexcept {
	return !(lhs == rhs);
}
template <TrivialElement T>
bool operator== (const Vector<T>& lhs, const HeapArray<T>& rhs) noexcept {
	static_assert(std::equality_comparable<T> && "Type must be totally ordered");
	if (lhs.size() != rhs.size())
		return false;

	return memcmp(lhs.data(), rhs.data(), lhs.size() * sizeof(T)) == 0;
}
template <TrivialElement T>
bool operator!= (const Vector<T>& lhs, const HeapArray<T>& rhs) noexcept {
	return !(lhs == rhs);
}
}