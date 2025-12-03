/*
	IDEA: Unsafe classes and safe classes
*/

#include <concepts>
#include <string>
#include <iostream>

#include "exceptionHandeling.hpp"

template<typename T>
concept UnsafePosibe = requires(T & obj) {
	{ reinterpret_cast<typename T::UnsafeType&>(obj) } -> std::same_as<typename T::UnsafeType&>;
};

struct FooData {
	int* _arr;
	size_t _size;
};

class UnsafeFoo
	: FooData {
public:
	UnsafeFoo() = delete;
	UnsafeFoo(size_t size)
		: FooData(new int[size], size) {}

	UnsafeFoo(const UnsafeFoo&) = delete;
	UnsafeFoo& operator=(const UnsafeFoo&) = delete;
	UnsafeFoo(UnsafeFoo&&) = delete;
	UnsafeFoo& operator=(UnsafeFoo&&) = delete;

	~UnsafeFoo() {
		delete[] _arr;
	}

	int& operator[](size_t index) noexcept {
		return _arr[index];
	}

	size_t size() noexcept {
		return _size;
	}
};

class Foo
	: FooData {
public:
	using UnsafeType = UnsafeFoo;

	Foo() = delete;
	Foo(size_t size)
		: FooData(new int[size](0), size) {}

	Foo(const Foo&) = delete;
	Foo& operator=(const Foo&) = delete;
	Foo(Foo&&) = delete;
	Foo& operator=(Foo&&) = delete;

	~Foo() {
		delete[] _arr;
	}

	Database::Expected<int> at(size_t index) NOEXCEPT {
		if (index >= _size)
			DATABASE_EXCEPTION_HANDLING_THROW_ERROR("Index out of range");
		return _arr[index];
	}

	size_t size() noexcept {
		return _size;
	}
};

template<UnsafePosibe T>
typename T::UnsafeType& UNSAFE(T& obj) {
	return reinterpret_cast<typename T::UnsafeType&>(obj);
}

// uses return value exceptions
void usageExample() {
	Foo a(10);
	if (a.at(1).has_value())
		std::cout << "error checked value: " << a.at(1).value() << "\n";
	if (!a.at(10).has_value())
		std::cout << "safty is king\n";


	std::cout << "fast but unsafe value: " << UNSAFE(a)[1] << "\n";

	//Acces fault may leed to program crach
	std::cout << "fast and incorect: " << UNSAFE(a)[10] << "\n";
}