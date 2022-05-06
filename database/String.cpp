#include "string.hpp"

#include "Vector.hpp"

namespace Database {

    String::String() {}
    String::String(const String& s) {
        *this = s;
    }

    String::String(char* s) {
        *this = s;
    }

    String::String(const size_t capacity) {
        stringVec = new Vector<char>(capacity);
    }

    String::~String() {}

    constexpr char String::operator[](size_t index) {
        return stringVec[index];
    }

    constexpr String String::operator()(size_t startIndex, size_t endIndex) {
    }

    constexpr String& String::operator+(String s);
    constexpr String& String::operator+(char* s);
    constexpr String& String::operator=(const String& s) {
        stringVec = s.stringVec;
        return *this;
    }

    constexpr String& String::operator=(char* s) {
        
        return *this;
    }
    constexpr bool String::operator==(String s);
    constexpr bool String::operator==(char* s);

    constexpr size_t String::length() {
        return stringVec.size();
    }

    constexpr void String::clear() {
        stringVec.clear();
    }
}