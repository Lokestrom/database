/*
Author: Loke Strøm
*/
#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include <concepts>
#include "Vector.hpp"
#include "exceptionHandeling.hpp"

namespace Database
{
class CharSpan;

class String {
public:
	String();
	String(const String& s);
	String(String&& s) noexcept;
	String(const char* s);
	String(const char* s, size_t length);
	String(const CharSpan& span);
	String(const std::string& s);

	~String() noexcept;

	String& operator=(const String& s);
	String& operator=(String&& s) noexcept;
	String& operator=(const char* s);
	String& operator=(const CharSpan& span);
	String& operator=(const std::string& s);

	//element accesses
	[[nodiscard]]
	char& operator[](const size_t index) noexcept;
	[[nodiscard]]
	const char& operator[](const size_t index) const noexcept;
	[[nodiscard]]
	Expected<String> operator()(const size_t startIndex, const size_t endIndex) const DATABASE_EXCEPTION_HANDLING_NOEXCEPT;

	[[nodiscard]]
	CharSpan span(const size_t startIndex, const size_t endIndex) const noexcept;

	[[nodiscard]]
	Expected<char&> at(const size_t index) DATABASE_EXCEPTION_HANDLING_NOEXCEPT;
	[[nodiscard]]
	Expected<const char&> at(const size_t index) const DATABASE_EXCEPTION_HANDLING_NOEXCEPT;

	[[nodiscard]]
	char* cstr() noexcept;
	[[nodiscard]]
	const char* cstr() const noexcept;


	//iterator
	[[nodiscard]]
	char* begin() noexcept;
	[[nodiscard]]
	char* end() noexcept;
	[[nodiscard]]
	const char* begin() const noexcept;
	[[nodiscard]]
	const char* end() const noexcept;

	//capacity
	[[nodiscard]]
	const bool isEmpty() const noexcept;
	[[nodiscard]]
	size_t capacity() const noexcept;
	[[nodiscard]]
	const size_t length() const noexcept;

	DATABASE_EXCEPTION_HANDLING_VOID_EXPECTED_NODISCARD
		Expected<void> reserve(const size_t newCapacity) DATABASE_EXCEPTION_HANDLING_NOEXCEPT;

	DATABASE_EXCEPTION_HANDLING_VOID_EXPECTED_NODISCARD
		Expected<void> shrinkToFit() DATABASE_EXCEPTION_HANDLING_NOEXCEPT;

	//operations
	String& operator+=(const String& s);
	String& operator+=(const char* s);

	DATABASE_EXCEPTION_HANDLING_VOID_EXPECTED_NODISCARD
		Expected<void> pushBack(const char val) DATABASE_EXCEPTION_HANDLING_NOEXCEPT;
	DATABASE_EXCEPTION_HANDLING_VOID_EXPECTED_NODISCARD
		Expected<void> insert(const size_t index, const String& s) DATABASE_EXCEPTION_HANDLING_NOEXCEPT;
	DATABASE_EXCEPTION_HANDLING_VOID_EXPECTED_NODISCARD
		Expected<void> insert(const size_t index, const char* s) DATABASE_EXCEPTION_HANDLING_NOEXCEPT;
	DATABASE_EXCEPTION_HANDLING_VOID_EXPECTED_NODISCARD
		Expected<void> insert(const size_t index, const char c) DATABASE_EXCEPTION_HANDLING_NOEXCEPT;
	DATABASE_EXCEPTION_HANDLING_VOID_EXPECTED_NODISCARD
		Expected<void> insert(const size_t index, const char* c, const size_t len) DATABASE_EXCEPTION_HANDLING_NOEXCEPT;

	DATABASE_EXCEPTION_HANDLING_VOID_EXPECTED_NODISCARD
		Expected<void> popBack() DATABASE_EXCEPTION_HANDLING_NOEXCEPT;

	DATABASE_EXCEPTION_HANDLING_VOID_EXPECTED_NODISCARD
		Expected<void> pop(const size_t index) DATABASE_EXCEPTION_HANDLING_NOEXCEPT;
	DATABASE_EXCEPTION_HANDLING_VOID_EXPECTED_NODISCARD
		Expected<void> pop(const size_t startIndex, const size_t endIndex) DATABASE_EXCEPTION_HANDLING_NOEXCEPT;

	void clear() noexcept;

	void lower() noexcept;
	void upper() noexcept;

	//search
	[[nodiscard]]
	bool contains(const String& target) const noexcept;
	[[nodiscard]]
	bool contains(const char target) const noexcept;
	[[nodiscard]]
	size_t binarySearch(const char target) const noexcept;
	[[nodiscard]]
	size_t linearSearch(const char target) const noexcept;
	[[nodiscard]]
	size_t linearSearch(const String& target) const noexcept;
	[[nodiscard]]
	size_t linearSearchR(const char target) const noexcept;
	[[nodiscard]]
	size_t linearSearchR(const String& target) const noexcept;


	//TODO: implement mergesort in o(1) space
	// saves heap allocation and can make it totally noexcept
	//sort
	DATABASE_EXCEPTION_HANDLING_VOID_EXPECTED_NODISCARD
		Expected<void> mergeSort() DATABASE_EXCEPTION_HANDLING_NOEXCEPT;
	void bubbleSort() noexcept;

	Expected<std::vector<String>> split(const char splitElement) const DATABASE_EXCEPTION_HANDLING_NOEXCEPT;
	Expected<std::vector<String>> split(const String& splitStr) const DATABASE_EXCEPTION_HANDLING_NOEXCEPT;
	DATABASE_EXCEPTION_HANDLING_VOID_EXPECTED_NODISCARD
		Expected<void> remove(const char element, size_t count) DATABASE_EXCEPTION_HANDLING_NOEXCEPT;
	DATABASE_EXCEPTION_HANDLING_VOID_EXPECTED_NODISCARD
		Expected<void> remove(const char element) DATABASE_EXCEPTION_HANDLING_NOEXCEPT;

	//non member functions
	friend bool operator==(const String& lhs, const String& rhs) noexcept;
	friend bool operator!=(const String& lhs, const String& rhs) noexcept;

	friend String operator+(const String& l, const String& r);
	friend String operator+(const String& l, const char* r);
	friend String operator+(const String& l, const char r);
	friend String operator+(const char* l, const String& r);

	friend std::ostream& operator<<(std::ostream& output, const String& s);
	friend std::istream& operator>>(std::istream& input, String& s);

private:
	void copyCharArray(const char* s, size_t len) noexcept;
	DATABASE_EXCEPTION_HANDLING_VOID_EXPECTED_NODISCARD
		Expected<void> allocateNewArray(size_t newCapacity) DATABASE_EXCEPTION_HANDLING_NOEXCEPT;

	DATABASE_EXCEPTION_HANDLING_VOID_EXPECTED_NODISCARD
		Expected<void> newArray(const char* s, size_t len) DATABASE_EXCEPTION_HANDLING_NOEXCEPT;
	DATABASE_EXCEPTION_HANDLING_VOID_EXPECTED_NODISCARD
		Expected<void> resizeArray(size_t newCapacity) DATABASE_EXCEPTION_HANDLING_NOEXCEPT;
	DATABASE_EXCEPTION_HANDLING_VOID_EXPECTED_NODISCARD
		Expected<void> resizeIfNeeded(size_t newExpectedSize) DATABASE_EXCEPTION_HANDLING_NOEXCEPT;

private:
	char* _arr = nullptr;
	size_t _currentSize = 0, _currentCapacity = 0;
};

class CharSpan {
public:
	constexpr CharSpan() noexcept : _data(nullptr), _size(0) {}

	constexpr CharSpan(const char* s) noexcept
		: _data(s),
		_size(s ? std::char_traits<char>::length(s) : 0) {}

	constexpr CharSpan(const char* s, size_t n) noexcept
		: _data(s), _size(n) {}

	CharSpan(String& str) noexcept
		: _data(str.cstr()), _size(str.length()) {}

	constexpr CharSpan(std::string_view sv) noexcept
		: _data(sv.data()), _size(sv.size()) {}

	template<std::convertible_to<std::string_view> T>
	constexpr CharSpan(T& t) noexcept
		: CharSpan(std::string_view(t)) {}

	template<typename T>
	constexpr CharSpan(const T& str) {
		constructor(*this, str);
	}

	template<typename T>
	static constexpr void constructor(CharSpan& span, const T& str) noexcept {
		static_assert(false && "Must define the Database::CharSpan::constructor function for the type");
	}

	[[nodiscard]]
	constexpr const char* begin() const noexcept {
		return _data;
	}
	[[nodiscard]]
	constexpr const char* end() const noexcept {
		return _data + _size;
	}
	[[nodiscard]]
	constexpr const size_t size() const noexcept {
		return _size;
	}
	[[nodiscard]]
	constexpr const char& operator[](size_t index) const noexcept {
		return _data[index];
	}
	[[nodiscard]]
	friend constexpr bool operator==(const CharSpan& lhs, const CharSpan& rhs) noexcept {
		return lhs._size == rhs._size && std::ranges::equal(lhs, rhs);
	}
	[[nodiscard]]
	friend constexpr bool operator!=(const CharSpan& lhs, const CharSpan& rhs) noexcept {
		return !(lhs == rhs);
	}

	template<std::ranges::range R>
	[[nodiscard]]
	friend bool operator==(const CharSpan& lhs,const R& rhs) {
		return std::ranges::size(rhs) == lhs._size &&
			std::ranges::equal(lhs, rhs);
	}

	template<std::ranges::range R>
	[[nodiscard]]
	friend bool operator==(const R& lhs, const CharSpan& rhs) {
		return std::ranges::size(lhs) == rhs._size &&
			std::ranges::equal(lhs, rhs);
	}

	template<std::ranges::range R>
	[[nodiscard]]
	friend bool operator!=(const CharSpan& lhs, const R& rhs) {
		return !(lhs == rhs);
	}

	template<std::ranges::range R>
	[[nodiscard]]
	friend bool operator!=(const R& lhs, const CharSpan& rhs) {
		return !(rhs == lhs);
	}

private:
	const char* _data;
	size_t _size;
};

template<typename T>
constexpr bool CharSpanConstructiorNoexceptV =
	noexcept(CharSpan::constructor(std::declval<CharSpan>(), std::declval<T>()));

//extra String functions
[[nodiscard]]
Expected<std::string> toSTD(const String& s) DATABASE_EXCEPTION_HANDLING_NOEXCEPT;

template<typename T>
concept Streamable = requires(const T& a, std::stringstream ss) {
	{ ss << a };
};

template<Streamable T>
[[nodiscard]] Expected<String> toS(const T& x) DATABASE_EXCEPTION_HANDLING_NOEXCEPT {
	DATABASE_EXCEPTION_HANDLING_HANDLE_EXCEPTION_BEGIN
	std::stringstream ss;
	ss << x;
	return ss.str();
	DATABASE_EXCEPTION_HANDLING_HANDLE_EXCEPTION_END
}

template<typename T>
concept StreamExtractable = requires(std::stringstream ss, T x) {
	{ ss >> x } -> std::same_as<std::stringstream&>;
};

template<typename T>
[[nodiscard]] T STo(const String& s) DATABASE_EXCEPTION_HANDLING_NOEXCEPT {
	DATABASE_EXCEPTION_HANDLING_HANDLE_EXCEPTION_BEGIN
	T x;
	std::stringstream ss(s.cstr());
	ss >> x;
	return x;
	DATABASE_EXCEPTION_HANDLING_HANDLE_EXCEPTION_END
}

[[nodiscard]]
size_t substringIndex(const String& s, const String& subS) noexcept;
[[nodiscard]]
bool canStringConvertToNumber(const String& x) noexcept;
[[nodiscard]]
Expected<bool> getline(std::ifstream& file, String& string) DATABASE_EXCEPTION_HANDLING_NOEXCEPT;

[[nodiscard]]
Expected<String> lower(const String& s) DATABASE_EXCEPTION_HANDLING_NOEXCEPT;
[[nodiscard]]
Expected<String> upper(const String& s) DATABASE_EXCEPTION_HANDLING_NOEXCEPT;
}

template<>
struct std::hash<Database::String> {
	size_t operator()(const Database::String& s) const;
};