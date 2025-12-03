/*
Author: Loke Str�m
*/
#include "String.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>
#include "Vector.hpp"

namespace Database
{
String::String() {
	_arr = new char[3];
	_currentCapacity = 3;
	_currentSize = 1;
	_arr[0] = '\0';
}
String::String(const String& s) {
	DATABASE_EXCEPTION_HANDLING_IF_EXPECTED_ERROR_THROW(newArray(s._arr, s.length()));
}
String::String(String&& s) noexcept {
	_arr = s._arr;
	_currentSize = s._currentSize;
	_currentCapacity = s._currentCapacity;
	s._arr = nullptr;
}
String::String(const char* s) {
	DATABASE_EXCEPTION_HANDLING_IF_EXPECTED_ERROR_THROW(newArray(s, std::char_traits<char>::length(s)));
}
String::String(const char* s, size_t length)
{
	DATABASE_EXCEPTION_HANDLING_IF_EXPECTED_ERROR_THROW(newArray(s, length));
}
String::String(const CharSpan& span)
{
	DATABASE_EXCEPTION_HANDLING_IF_EXPECTED_ERROR_THROW(newArray(span.begin(), span.size()));
}
String::String(const std::string& s) {
	DATABASE_EXCEPTION_HANDLING_IF_EXPECTED_ERROR_THROW(newArray(s.c_str(), s.length()));
}

String::~String() noexcept {
	delete[] _arr;
}

String& String::operator=(const String& s) {
	DATABASE_EXCEPTION_HANDLING_IF_EXPECTED_ERROR_THROW(newArray(s._arr, s.length()));
	return *this;
}
String& String::operator=(String&& s) noexcept {
	_arr = s._arr;
	_currentSize = s._currentSize;
	_currentCapacity = s._currentCapacity;
	s._arr = nullptr;

	return *this;
}
String& String::operator=(const char* s) {
	DATABASE_EXCEPTION_HANDLING_IF_EXPECTED_ERROR_THROW(newArray(s, std::char_traits<char>::length(s)));
	return *this;
}
String& String::operator=(const CharSpan& span)
{
	DATABASE_EXCEPTION_HANDLING_IF_EXPECTED_ERROR_THROW(newArray(span.begin(), span.size()));
	return *this;
}
String& String::operator=(const std::string& s) {
	DATABASE_EXCEPTION_HANDLING_IF_EXPECTED_ERROR_THROW(newArray(s.c_str(), s.length()));
	return *this;
}

char& String::operator[](const size_t index) noexcept {
	return _arr[index];
}
const char& String::operator[](const size_t index) const noexcept {
	return _arr[index];
}

Expected<String> String::operator()(const size_t startIndex, const size_t endIndex) const NOEXCEPT {
	if (startIndex >= this->length())
		DATABASE_EXCEPTION_HANDLING_THROW_ERROR("startIndex out of range");
	if (endIndex > this->length())
		DATABASE_EXCEPTION_HANDLING_THROW_ERROR("endIndex out of range");
	if (startIndex > endIndex)
		DATABASE_EXCEPTION_HANDLING_THROW_ERROR("startIndex can't be greater than endIndex");
	DATABASE_EXCEPTION_HANDLING_HANDLE_EXCEPTION_BEGIN
	String x;
	DATABASE_EXCEPTION_HANDLING_PROPEGATE_ERROR(x.newArray(&_arr[startIndex], endIndex - startIndex));
	return x;
	DATABASE_EXCEPTION_HANDLING_HANDLE_EXCEPTION_END
}

CharSpan String::span(const size_t startIndex, const size_t endIndex) const noexcept {
	return CharSpan(&_arr[startIndex], endIndex - startIndex);
}

Expected<char&> String::at(const size_t index) {
	if (index >= this->length())
		DATABASE_EXCEPTION_HANDLING_THROW_ERROR("index out of range");
	return _arr[index];
}
Expected<const char&> String::at(const size_t index) const {
	if (index >= this->length())
		DATABASE_EXCEPTION_HANDLING_THROW_ERROR("index out of range");
	return _arr[index];
}

char* String::cstr() noexcept {
	return _arr;
}

const char* String::cstr() const noexcept {
	return _arr;
}

char* String::begin() noexcept {
	return _arr;
}

char* String::end() noexcept {
	return &_arr[this->length()];
}

const char* String::begin() const noexcept {
	return _arr;
}

const char* String::end() const noexcept {
	return &_arr[this->length()];
}

const bool String::isEmpty() const noexcept {
	return _currentSize == 1;
}

size_t String::capacity() const noexcept {
	return _currentCapacity - 1;
}

const size_t String::length() const noexcept {
	return _currentSize - 1;
}

Expected<void> String::reserve(size_t newCapacity) NOEXCEPT {
	if (newCapacity < _currentCapacity) {
		DATABASE_EXCEPTION_HANDLING_THROW_ERROR("newCapacity can't be less than currentCapacity");
	}
	DATABASE_EXCEPTION_HANDLING_PROPEGATE_ERROR(resizeArray(newCapacity + 1));
}
Expected<void> String::shrinkToFit() NOEXCEPT {
	DATABASE_EXCEPTION_HANDLING_PROPEGATE_ERROR(resizeArray(_currentSize));
}

String& String::operator+=(const String& s) {
	DATABASE_EXCEPTION_HANDLING_IF_EXPECTED_ERROR_THROW(this->insert(this->length(), s));
	return *this;
}

String& String::operator+=(const char* s) {
	DATABASE_EXCEPTION_HANDLING_IF_EXPECTED_ERROR_THROW(this->insert(this->length(), s));
	return *this;
}

Expected<void> String::pushBack(const char val) NOEXCEPT {
	DATABASE_EXCEPTION_HANDLING_PROPEGATE_ERROR(resizeIfNeeded(_currentSize + 1));
	_arr[this->length()] = val;
	_arr[_currentSize] = '\0';
	_currentSize++;
}

Expected<void> String::insert(const size_t index, const String& s) NOEXCEPT {
	DATABASE_EXCEPTION_HANDLING_PROPEGATE_ERROR(insert(index, s.cstr(), s.length()));
}
Expected<void> String::insert(size_t index, const char* s) NOEXCEPT {
	DATABASE_EXCEPTION_HANDLING_PROPEGATE_ERROR(insert(index, s, std::char_traits<char>::length(s)));
}
Expected<void> String::insert(const size_t index, char c) NOEXCEPT {
	if (index > this->length())
		DATABASE_EXCEPTION_HANDLING_THROW_ERROR("Index out of range");
	DATABASE_EXCEPTION_HANDLING_PROPEGATE_ERROR(resizeIfNeeded(_currentSize + 1));
	std::memmove(&_arr[index + 1], &_arr[index], _currentSize - index);
	_arr[index] = c;
	_currentSize++;
}

Expected<void> String::insert(const size_t index, const char* c, const size_t len) NOEXCEPT {
	if (index > this->length())
		DATABASE_EXCEPTION_HANDLING_THROW_ERROR("Index out of range");

	DATABASE_EXCEPTION_HANDLING_PROPEGATE_ERROR(resizeIfNeeded(_currentSize + len));
	std::memmove(&_arr[index + len], &_arr[index], _currentSize - index);
	std::memcpy(&_arr[index], c, len);
	_currentSize += len;
}

Expected<void> String::popBack() NOEXCEPT {
	if (this->length() == 0)
		DATABASE_EXCEPTION_HANDLING_THROW_ERROR("Can't popBack on empty Vector");

	_currentSize--;
	_arr[_currentSize - 1] = '\0';
}

Expected<void> String::pop(const size_t index) NOEXCEPT {
	if (index >= this->length())
		DATABASE_EXCEPTION_HANDLING_THROW_ERROR("Index out of range");
	_currentSize--;
	std::memmove(&_arr[index], &_arr[index + 1], _currentSize - index);
}
Expected<void> String::pop(const size_t startIndex, const size_t endIndex) NOEXCEPT {
	if (endIndex > this->length())
		DATABASE_EXCEPTION_HANDLING_THROW_ERROR("endIndex out of range");
	if (startIndex > endIndex)
		DATABASE_EXCEPTION_HANDLING_THROW_ERROR("startIndex can't be greater than endIndex");
	//if startIndex is less than endIndex, and endIndex is less than length, startIndex is automatically less than length

	std::memmove(&_arr[startIndex], &_arr[endIndex], _currentSize - endIndex);
	_currentSize -= endIndex - startIndex;
}

void String::clear() noexcept {
	_currentSize = 1;
	_arr[0] = '\0';
}

void String::lower() noexcept {
	for (char& i : *this)
		if (i <= 'Z' && i >= 'A')
			i += 32;
}

void String::upper() noexcept {
	for (char& i : *this)
		if (i <= 'z' && i >= 'a')
			i -= 32;
}

bool String::contains(const String& target) const noexcept {
	bool isSubS = false;
	for (auto i = 0; i < (*this).length(); i++) {
		if ((*this)[i] == target[0]) {
			isSubS = true;
			for (auto j = 0; j < target.length(); j++)
				if ((*this)[j + i] != target[j])
					isSubS = false;
		}
		if (isSubS)
			return true;
	}
	return false;
}

bool String::contains(const char target) const noexcept {
	for (auto i : *this)
		if (i == target)
			return true;
	return false;
}

size_t String::binarySearch(const char target) const noexcept {
	size_t low = 0;
	size_t high = this->length() - 1;
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
	return this->length();
}

size_t String::linearSearch(const char target) const noexcept {
	for (auto i = 0; i < this->length(); i++)
		if (_arr[i] == target)
			return i;
	return this->length();
}
size_t String::linearSearchR(const char target) const noexcept {
	for (long long i = this->length() - 1; i > -1; i--)
		if (_arr[i] == target)
			return i;
	return this->length();
}

Expected<void> String::mergeSort() NOEXCEPT {
	if (this->length() == 1)
		return;
	DATABASE_EXCEPTION_HANDLING_HANDLE_EXCEPTION_BEGIN
	String start;
	DATABASE_EXCEPTION_HANDLING_TRY_ASSIGN(start, this->operator()(0, this->length() / 2));
	String end;
	DATABASE_EXCEPTION_HANDLING_TRY_ASSIGN(end, this->operator()(this->length() / 2, this->length()));

	DATABASE_EXCEPTION_HANDLING_PROPEGATE_ERROR(start.mergeSort());
	DATABASE_EXCEPTION_HANDLING_PROPEGATE_ERROR(end.mergeSort());

	clear();

	size_t startPos = 0, endPos = 0;

	while (startPos != start.length() && endPos != end.length()) {
		if (start[startPos] < end[endPos]) {
			DATABASE_EXCEPTION_HANDLING_SAFE_GARANTEE(pushBack(start[startPos]));
			startPos++;
		}
		else {
			DATABASE_EXCEPTION_HANDLING_SAFE_GARANTEE(pushBack(end[endPos]));
			endPos++;
		}
	}

	for (; startPos != start.length(); startPos++)
		DATABASE_EXCEPTION_HANDLING_SAFE_GARANTEE(pushBack(start[startPos]));
	for (; endPos != end.length(); endPos++)
		DATABASE_EXCEPTION_HANDLING_SAFE_GARANTEE(pushBack(end[endPos]));
	DATABASE_EXCEPTION_HANDLING_HANDLE_EXCEPTION_END
}

void String::bubbleSort() noexcept {
	char temp;
	for (auto i = 0; i < this->length(); i++) {
		for (auto j = 0; j < this->length() - i - 1; j++) {
			if (_arr[j] > _arr[j + 1]) {
				temp = _arr[j + 1];
				_arr[j + 1] = _arr[j];
				_arr[j] = temp;
			}
		}
	}
}

Expected<std::vector<String>> String::split(const char splitElement) const NOEXCEPT {
	DATABASE_EXCEPTION_HANDLING_HANDLE_EXCEPTION_BEGIN
	std::vector<String> splitStrings;
	String currentString;
	for (size_t i = 0; i < this->length(); i++) {
		if (_arr[i] == splitElement && !currentString.isEmpty()) {
			splitStrings.push_back(currentString);
			currentString.clear();
		}
		else if (_arr[i] != splitElement) {
			DATABASE_EXCEPTION_HANDLING_PROPEGATE_ERROR(currentString.pushBack(_arr[i]));
		}
	}
	if (!currentString.isEmpty())
		splitStrings.push_back(currentString);
	return splitStrings;
	DATABASE_EXCEPTION_HANDLING_HANDLE_EXCEPTION_END
}
Expected<void> String::remove(const char element) NOEXCEPT {
	DATABASE_EXCEPTION_HANDLING_HANDLE_EXCEPTION_BEGIN
	String removedString;
	DATABASE_EXCEPTION_HANDLING_PROPEGATE_ERROR(removedString.reserve(this->length()));
	for (size_t i = 0; i < this->length(); i++) {
		if (_arr[i] != element) {
			DATABASE_EXCEPTION_HANDLING_SAFE_GARANTEE(removedString.pushBack(_arr[i]));
		}
	}
	*this = std::move(removedString);
	DATABASE_EXCEPTION_HANDLING_HANDLE_EXCEPTION_END
}
Expected<void> String::remove(const char element, size_t count) NOEXCEPT {
	if (count > this->length()) {
		DATABASE_EXCEPTION_HANDLING_THROW_ERROR("Count can't be greater than length");
	}
	DATABASE_EXCEPTION_HANDLING_HANDLE_EXCEPTION_BEGIN
	String removedString;
	DATABASE_EXCEPTION_HANDLING_PROPEGATE_ERROR(removedString.reserve(this->length() - count));
	size_t i = 0;
	for (; i < this->length() && count > 0; i++) {
		if (_arr[i] != element) {
			DATABASE_EXCEPTION_HANDLING_SAFE_GARANTEE(removedString.pushBack(_arr[i]));
			continue;
		}
		count--;
	}
	for (; i < this->length(); i++) {
		DATABASE_EXCEPTION_HANDLING_SAFE_GARANTEE(removedString.pushBack(_arr[i]));
	}
	*this = std::move(removedString);
	DATABASE_EXCEPTION_HANDLING_HANDLE_EXCEPTION_END
}

void String::copyCharArray(const char* s, size_t len) noexcept {
	std::memcpy(_arr, s, len);
	_arr[len] = '\0';
	_currentSize = len + 1;
}

Expected<void> String::allocateNewArray(size_t newCapacity) NOEXCEPT {
	delete[] _arr;
	DATABASE_EXCEPTION_HANDLING_HANDLE_EXCEPTION_BEGIN
	_arr = new char[newCapacity];
	DATABASE_EXCEPTION_HANDLING_HANDLE_EXCEPTION_END
	_currentCapacity = newCapacity;
}
Expected<void> String::newArray(const char* s, size_t len) NOEXCEPT {
	DATABASE_EXCEPTION_HANDLING_PROPEGATE_ERROR(allocateNewArray(len + 1));
	copyCharArray(s, len);
}
Expected<void> String::resizeArray(size_t newCapacity) NOEXCEPT {
	DATABASE_EXCEPTION_HANDLING_HANDLE_EXCEPTION_BEGIN
	char* temp = new char[newCapacity];
	std::memcpy(temp, _arr, _currentSize);
	delete[] _arr;
	_arr = temp;
	DATABASE_EXCEPTION_HANDLING_HANDLE_EXCEPTION_END
	_currentCapacity = newCapacity;
}
Expected<void> String::resizeIfNeeded(size_t newExpectedSize) NOEXCEPT {
	if (newExpectedSize >= _currentCapacity) {
		size_t newCap = newExpectedSize + (newExpectedSize / 2) + 2;
		DATABASE_EXCEPTION_HANDLING_PROPEGATE_ERROR(resizeArray(newCap));
	}
}
}

namespace Database
{
String operator+(const String& l, const String& r) {
	String s(l);
	s += r;
	return s;
}
String operator+(const String& l, const char* r) {
	String s(l);
	s += r;
	return s;
}
String operator+(const String& l, const char r) {
	String s(l);
	s.pushBack(r);
	return s;
}
String operator+(const char* l, const String& r) {
	String s(l);
	s += r;
	return s;
}

bool operator==(const String& lsh, const String& rsh) noexcept {
	if (lsh.length() != rsh.length())
		return false;

	for (auto i = 0; i < lsh.length(); i++)
		if (lsh[i] != rsh[i])
			return false;
	return true;
}
bool operator!=(const String& lsh, const String& rsh) noexcept {
	return !(lsh == rsh);
}

std::ostream& operator<<(std::ostream& output, const String& s) noexcept {
	for (const char& i : s)
		output << i;
	return output;
}
std::ofstream& operator<<(std::ofstream& output, const String& s) noexcept {
	for (const char& i : s)
		output << i;
	return output;
}

std::istream& operator>>(std::istream& input, String& s) noexcept {
	char* buff = new char[1024];
	input.getline(buff, 1024);
	s = buff;
	delete[] buff;
	return input;
}
std::ifstream& operator>>(std::ifstream& input, String& s) noexcept {
	char* buff = new char[1024];
	input.getline(buff, 1024);
	s = buff;
	delete[] buff;
	return input;
}

Expected<std::string> toSTD(const String& s) NOEXCEPT {
	DATABASE_EXCEPTION_HANDLING_HANDLE_EXCEPTION_BEGIN
	std::string r;
	r.reserve(s.length());
	for (const char& c : s)
		r.push_back(c);
	return r;
	DATABASE_EXCEPTION_HANDLING_HANDLE_EXCEPTION_END
}

size_t substringIndex(const String& s, const String& subS) noexcept {
	long long isSubS = 0;
	for (auto i = 0; i < s.length(); i++) {
		if (s[i] == subS[0]) {
			isSubS = i;
			for (auto j = 0; j < subS.length(); j++)
				if (s[j + i] != subS[j])
					isSubS = 0;
		}
		if (isSubS)
			return isSubS;
	}
	return s.length();
}

bool canStringConvertToNumber(const String& s) noexcept {
	for (const char& i : s)
		if (i != '0' && i != '1' && i != '2' && i != '3' && i != '4' && i != '5' && i != '6' && i != '7' && i != '8' && i != '9' && i != '.' && i != '-' && i != 'E')
			return false;
	return true;
}

Expected<bool> getline(std::ifstream& file, String& string) NOEXCEPT {
	DATABASE_EXCEPTION_HANDLING_HANDLE_EXCEPTION_BEGIN
	if (file.eof())
		return false;
	std::string text;
	std::getline(file, text);
	string = text;
	return true;
	DATABASE_EXCEPTION_HANDLING_HANDLE_EXCEPTION_END
}
Expected<String> lower(const String& s) NOEXCEPT {
	DATABASE_EXCEPTION_HANDLING_HANDLE_EXCEPTION_BEGIN
	String ans = s;
	for (char& i : ans)
		if (i <= 'Z' && i >= 'A')
			i += 32;
	return ans;
	DATABASE_EXCEPTION_HANDLING_HANDLE_EXCEPTION_END
}
Expected<String> upper(const String& s) NOEXCEPT {
	DATABASE_EXCEPTION_HANDLING_HANDLE_EXCEPTION_BEGIN
	String ans = s;
	for (char& i : ans)
		if (i <= 'z' && i >= 'a')
			i -= 32;
	return ans;
	DATABASE_EXCEPTION_HANDLING_HANDLE_EXCEPTION_END
}
}

size_t std::hash<Database::String>::operator()(const Database::String& s) const {
	return std::hash<std::string>{}(DATABASE_EXCEPTION_HANDLING_IF_EXPECTED_ERROR_THROW(Database::toSTD(s)));
}