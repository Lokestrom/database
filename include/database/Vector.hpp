#pragma once

#include <concepts>
#include <vector>
#include "exceptionHandeling.hpp"

namespace Database
{

template <typename T>
concept TrivialElement =
std::is_trivially_destructible_v<T> &&
std::is_trivially_copyable_v<T>;


template <TrivialElement T>
class HeapArray;


template <TrivialElement T>
class Vector {
public:
	Vector() noexcept;
	Vector(const Vector<T>& vector);
	Vector(Vector<T>&& vector) noexcept;
	Vector(const std::initializer_list<T>& initializerList);
	Vector(const std::vector<T>& vector);
	explicit Vector(const size_t capacity);
	Vector(const size_t count, const T& value);
	~Vector() noexcept;

	T& operator[] (const size_t index) noexcept;
	const T& operator[] (const size_t index) const noexcept;
	Expected<Vector<T>> operator() (const size_t startIndex, const size_t endIndex) const NOEXCEPT;

	Vector<T>& operator= (const Vector<T>& vector);
	Vector<T>& operator= (Vector<T>&& vector) noexcept;
	Vector<T>& operator= (const std::initializer_list<T> initializerList);

	Vector<T>& operator+= (const Vector<T>& vector);

	[[nodiscard]]
	Expected<T&> at(const size_t index) NOEXCEPT;
	[[nodiscard]]
	Expected<const T&> at(const size_t index) const NOEXCEPT;
	[[nodiscard]]
	bool empty() const noexcept;
	[[nodiscard]]
	void clear() noexcept;
	[[nodiscard]]
	size_t size() const noexcept;
	[[nodiscard]]
	size_t capacity() const noexcept;
	DATABASE_EXCEPTION_HANDLING_VOID_EXPECTED_NODISCARD
	Expected<void> reserve(const size_t newCapacity) NOEXCEPT;
	[[nodiscard]]
	T* data() noexcept;
	[[nodiscard]]
	const T* data() const noexcept;
	DATABASE_EXCEPTION_HANDLING_VOID_EXPECTED_NODISCARD
	Expected<void> shrinkToFit() NOEXCEPT;

	[[nodiscard]]
	T* begin() noexcept;
	[[nodiscard]]
	T* end() noexcept;

	[[nodiscard]]
	const T* begin() const noexcept;
	[[nodiscard]]
	const T* end() const noexcept;

	DATABASE_EXCEPTION_HANDLING_VOID_EXPECTED_NODISCARD
	Expected<void> pushBack(const T& val) NOEXCEPT;
	Expected<void> popBack() NOEXCEPT;

	DATABASE_EXCEPTION_HANDLING_VOID_EXPECTED_NODISCARD
	Expected<void> insert(const size_t index, T val) NOEXCEPT;
	DATABASE_EXCEPTION_HANDLING_VOID_EXPECTED_NODISCARD
	Expected<void> insert(const size_t index, const Vector<T>& vector);
	DATABASE_EXCEPTION_HANDLING_VOID_EXPECTED_NODISCARD
	Expected<void> insert(const size_t index, const std::initializer_list<T> initializerList);

	Expected<void> pop(const size_t index) NOEXCEPT;
	Expected<void> pop(const size_t startIndex, const size_t endIndex) NOEXCEPT;

	//TODO: implement mergesort in o(1) space
	// saves heap allocation and can make it totally noexcept
	DATABASE_EXCEPTION_HANDLING_VOID_EXPECTED_NODISCARD
	Expected<void> mergeSort() NOEXCEPT;
	void bubbleSort() noexcept;

	size_t binarySearch(const T target) const noexcept;
	size_t linearSearch(const T target) const noexcept;
	size_t linearSearchR(const T target) const noexcept;

public:
	template<TrivialElement T>
	friend bool operator== (const Vector<T>& lhs, const Vector<T>& rhs) noexcept;
	template<TrivialElement T>
	friend bool operator!= (const Vector<T>& lhs, const Vector<T>& rhs) noexcept;
	template<TrivialElement T>
	friend bool operator== (const HeapArray<T>& lhs, const Vector<T>& rhs) noexcept;
	template<TrivialElement T>
	friend bool operator!= (const HeapArray<T>& lhs, const Vector<T>& rhs) noexcept;
	template<TrivialElement T>
	friend bool operator== (const Vector<T>& lhs, const HeapArray<T>& rhs) noexcept;
	template<TrivialElement T>
	friend bool operator!= (const Vector<T>& lhs, const HeapArray<T>& rhs) noexcept;

private:
	void copyArray(const T* s, size_t len) noexcept;
	DATABASE_EXCEPTION_HANDLING_VOID_EXPECTED_NODISCARD
	Expected<void> allocateNewArray(size_t newCapacity) NOEXCEPT;
	DATABASE_EXCEPTION_HANDLING_VOID_EXPECTED_NODISCARD
	Expected<void> newArray(const T* s, size_t len) NOEXCEPT;
	DATABASE_EXCEPTION_HANDLING_VOID_EXPECTED_NODISCARD
	Expected<void> resizeArray(size_t newCapacity) NOEXCEPT;
	DATABASE_EXCEPTION_HANDLING_VOID_EXPECTED_NODISCARD
	Expected<void> resizeIfNeeded(size_t newExpectedSize) NOEXCEPT;

	T* _arr = nullptr;
	size_t _currentSize = 0, _currentCapacity = 0;
};

template<TrivialElement T>
class HeapArray {
public:
	HeapArray() = delete;
	HeapArray(size_t size);
	HeapArray(T* data, size_t size);
	~HeapArray() noexcept;

	HeapArray(const HeapArray<T>& other);
	HeapArray<T>& operator=(const HeapArray<T>& other);
	HeapArray(HeapArray<T>&&) noexcept;
	HeapArray<T>& operator=(HeapArray<T>&&) noexcept;

	T& operator[](size_t index) noexcept;
	const T& operator[](size_t index) const noexcept;

	T* begin() noexcept;
	const T* begin() const noexcept;

	T* end() noexcept;
	const T* end() const noexcept;

	size_t size() const noexcept;

	T* data() noexcept;
	const T* data() const noexcept;

	template<TrivialElement T>
	friend bool operator== (const HeapArray<T>& lhs, const HeapArray<T>& rhs) noexcept;
	template<TrivialElement T>
	friend bool operator!= (const HeapArray<T>& lhs, const HeapArray<T>& rhs) noexcept;
	template<TrivialElement T>
	friend bool operator== (const HeapArray<T>& lhs, const Vector<T>& rhs) noexcept;
	template<TrivialElement T>
	friend bool operator!= (const HeapArray<T>& lhs, const Vector<T>& rhs) noexcept;
	template<TrivialElement T>
	friend bool operator== (const Vector<T>& lhs, const HeapArray<T>& rhs) noexcept;
	template<TrivialElement T>
	friend bool operator!= (const Vector<T>& lhs, const HeapArray<T>& rhs) noexcept;

private:
	T* _arr;
	size_t _size;
};
}

#include "TemplateFiles/Vector.tpp"

