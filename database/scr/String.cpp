/*
Athor: Loke Str�m
*/
#include "string.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include "Exception.hpp"
#include "Vector.hpp"

namespace Database {
    constexpr String::String() noexcept {}
    String::String(const String& s) noexcept {
        *this = s;
    }
    String::String(String&& s) noexcept {
        *this = s;
    }
    constexpr String::String(const char* s) noexcept {
        *this = s;
    }
    String::String(const Vector<char>& v) noexcept {
        stringVec = v;
    }
    String::String(const std::string& s) noexcept {
        *this = s;
    }

    String& String::operator=(const String& s) noexcept {
        stringVec = s.stringVec;
        return *this;
    }
    String& String::operator=(String&& s) noexcept {
        stringVec = s.stringVec;
        return *this;
    }
    constexpr String& String::operator=(const char* s) noexcept {
        stringVec.clear();
        if (s == nullptr)
            return *this;
        for (const char* ptr = s; *ptr != '\0'; ptr++)
            stringVec.pushBack(*ptr);
        return *this;
    }
    String& String::operator=(const std::string& s) {
        stringVec.clear();
        for (const char& i : s)
            stringVec.pushBack(i);
        return *this;
    }
    String& String::operator=(const Vector<char>& s) {
        stringVec = s;
        return *this;
    }
    String& String::operator=(const std::initializer_list<char>& iList) noexcept {
        stringVec = iList;
        return *this;
    }


    constexpr char& String::operator[](const size_t index) noexcept {
        return stringVec[index];
    }
    constexpr char& String::operator[](const size_t index) const noexcept {
        return stringVec[index];
    }

    String String::operator()(const size_t startIndex, const size_t endIndex) const {
        if (startIndex >= stringVec.size())
            throw OutOfRange("startIndex out of range");
        if (endIndex > stringVec.size())
            throw OutOfRange("endIndex out of range");
        if (startIndex > endIndex)
            throw OutOfRange("startIndex can't be greater than endIndex");
        return String(stringVec(startIndex, endIndex));
    }

    constexpr char& String::at(const size_t index) {
        if (index >= stringVec.size())
            throw OutOfRange("index out of range");
        return stringVec[index];
    }
    constexpr char& String::at(const size_t index) const {
        if (index >= stringVec.size())
            throw OutOfRange("index out of range");
        return stringVec[index];
    }

    const char* String::cstr() noexcept {
        stringVec.pushBack('\0');
        return stringVec.data();
    }
    const char* String::cstr() const noexcept {
        Vector<char> temp = stringVec;
        temp.pushBack('\0');
        return temp.data();
    }

    Vector<char>& String::vectorData() noexcept {
        return stringVec;
    }
    Vector<char> String::vectorData() const noexcept {
        return stringVec;
    }

    char* String::begin() noexcept {
        return stringVec.begin();
    }
    char* String::begin() const noexcept {
        return stringVec.begin();
    }

    char* String::end() noexcept {
        return stringVec.end();
    }
    char* String::end() const noexcept {
        return stringVec.end();
    }

    const bool String::empty() noexcept {
        return stringVec.empty();
    }

    size_t String::capacity() noexcept {
        return stringVec.capacity();
    }

    const size_t String::length() const noexcept {
        return stringVec.size();
    }

    constexpr void String::reserve(const size_t newCapacity) noexcept {
        stringVec.reserve(newCapacity);
    }
    constexpr void String::shrinkToFit() noexcept {
        stringVec.shrinkToFit();
    }

    String& String::operator+=(const String s) noexcept {
        stringVec.insert(stringVec.size(), s.stringVec);
        return *this;
    }

    constexpr String& String::operator+=(const char* s) noexcept {
        for (const char* ptr = s; *ptr != '\0'; ptr++)
            stringVec.pushBack(*ptr);
        return *this;
    }

    constexpr void String::pushBack(const char val) noexcept {
        stringVec.pushBack(val);
    }

    void String::insert(const size_t index, const String& s) {
        stringVec.insert(index, s.stringVec);
    }
    void String::insert(size_t index, const char* s) {
        if (index > stringVec.size())
            throw OutOfRange("index out of range");
        for (const char* ptr = s; *ptr != '\0'; ptr++)
            stringVec.insert(index++, *ptr);
    }
    void String::insert(size_t index, const char c) {
        stringVec.insert(index, { c });
    }
    constexpr void String::insert(const size_t index, const Vector<char>& vector) {
        stringVec.insert(index, vector);
    }
    constexpr void String::insert(const size_t index, const std::initializer_list<char>& initializerList) {
        stringVec.insert(index, initializerList);
    }

    void String::popBack() {
        stringVec.popBack();
    }

    void String::pop(const size_t index) {
        stringVec.pop(index);
    }
    void String::pop(const size_t startIndex, const size_t endIndex) {
        stringVec.pop(startIndex, endIndex);
    }

    const void String::clear() noexcept {
        stringVec.clear();
    }

    const bool String::contains(const String& target) noexcept {
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

    const void String::lower() noexcept {
        for (char& i : *this)
            if (i <= 'Z' && i >= 'A')
                i += 32;
    }

    const void String::upper() noexcept {
        for (char& i : *this)
            if (i <= 'z' && i >= 'a')
                i -= 32;
    }

    long long String::binarySearch(const char target) noexcept {
        return stringVec.binarySearch(target);
    }

    long long String::linearSearch(const char target) noexcept {
        return stringVec.linearSearch(target);
    }
    long long String::linearSearchR(const char target) noexcept {
        return stringVec.linearSearchR(target);
    }

    constexpr void String::mergeSort() noexcept {
        stringVec.mergeSort();
    }

    constexpr void String::bubbleSort() noexcept {
        stringVec.bubbleSort();
    }

    const Vector<String> String::split(const char splitElement) const noexcept {
        Vector<String> splitStrings;
        String currentString;
        for (const char& c : stringVec) {
            if (c == splitElement) {
                splitStrings.pushBack(currentString);
                currentString.clear();
            }
            else {
                currentString.pushBack(c);
            }
        }
        splitStrings.pushBack(currentString);
        return splitStrings;
    }

    const void String::remove(const char element) noexcept {
        String removedString;
        for (const char& c : stringVec)
            if (c != element)
                removedString.pushBack(c);
        *this = std::move(removedString);
    }
}

namespace Database {

    //operator+
    const String operator+(const String& l, const String& r) noexcept {
        String s(l);
        s += r;
        return s;
    }
    const String operator+(const String& l, const char* r) noexcept {
        String s(l);
        s += r;
        return s;
    }
    const String operator+(const String& l, const char r) noexcept {
        String s(l);
        s.pushBack(r);
        return s;
    }
    const String operator+(const char* l, const String& r) noexcept {
        String s(l);
        s += r;
        return s;
    }
    
    //
    const bool operator==(const String& lsh, const String& rsh) noexcept {
        return lsh.stringVec == rsh.stringVec;
    }
    const bool operator!=(const String& lsh, const String& rsh) noexcept {
        return lsh.stringVec != rsh.stringVec;
    }

    //
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

    //
    std::istream& operator>>(std::istream& input, String& s) noexcept { 
        char* buff = new char[1000];
        input.getline(buff, 1000);
        s = buff;
        delete[] buff;
        return input;
    }
    std::ifstream& operator>>(std::ifstream& input, String& s) noexcept {
        char* buff = new char[1000];
        input.getline(buff, 1000);
        s = buff;
        delete[] buff;
        return input;
    }

    std::string toSTD(const String& s) {
        std::string r;
        r.reserve(s.length());
        for (const char& c : s)
            r.push_back(c);
        return r;
    }

    //tos
    String toS(const int x) {
        std::stringstream ss;
        String s;
        ss << x;
        s = ss.str();
        return s;
    }
    String toS(const long x) {
        std::stringstream ss;
        String s;
        ss << x;
        s = ss.str();
        return s;
    }
    String toS(const long long x){
        std::stringstream ss;
        String s;
        ss << x;
        s = ss.str();
        return s;
    }
    String toS(const unsigned x){
        std::stringstream ss;
        String s;
        ss << x;
        s = ss.str();
        return s;
    }
    String toS(const unsigned long x){
        std::stringstream ss;
        String s;
        ss << x;
        s = ss.str();
        return s;
    }
    String toS(const unsigned long long x){
        std::stringstream ss;
        String s;
        ss << x;
        s = ss.str();
        return s;
    }
    String toS(const double x) {
        std::stringstream ss;
        String s;
        ss << x;
        s = ss.str();
        return s;
    }
    String toS(const long double x) {
        std::stringstream ss;
        String s;
        ss << x;
        s = ss.str();
        return s;
    }

    //to number
    int SToi(const String& s) {
        std::stringstream ss;
        int x;
        ss << s;
        ss >> x;
        return x;
    }
    long STol(const String& s) {
        std::stringstream ss;
        long x;
        ss << s;
        ss >> x;
        return x;
    }
    long long SToll(const String& s) {
        std::stringstream ss;
        long long x;
        ss << s;
        ss >> x;
        return x;
    }
    unsigned STou(const String& s) {
        std::stringstream ss;
        unsigned x;
        ss << s;
        ss >> x;
        return x;
    }
    unsigned long SToul(const String& s) {
        std::stringstream ss;
        unsigned long x;
        ss << s;
        ss >> x;
        return x;
    }
    unsigned long long SToull(const String& s){
        std::stringstream ss;
        unsigned long long x;
        ss << s;
        ss >> x;
        return x;
    }
    double STod(const String& s){
        std::stringstream ss;
        double x;
        ss << s;
        ss >> x;
        return x;
    }
    long double STold(const String& s){
        std::stringstream ss;
        long double x;
        ss << s;
        ss >> x;
        return x;
    }

    //subStringIndex
    long long substringIndex(const String& s, const String& subS) {
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
        return -1;
    }

    bool canStringConvertToNumber(const String& s) {
        for (const char& i : s)
            if (i != '0' && i != '1' && i != '2' && i != '3' && i != '4' && i != '5' && i != '6' && i != '7' && i != '8' && i != '9' && i != '.' && i != '-')
                return false;
        return true;
    }

    bool getline(std::ifstream& file, String& string)
    {
        if (file.eof())
            return false;
        std::string text;
        std::getline(file, text);
        string = text;
        return true;
    }
    String lower(const String& s) noexcept
    {
        String ans = s;
        for (char& i : ans)
            if (i <= 'Z' && i >= 'A')
                i += 32;
        return ans;
    }
    String upper(const String& s) noexcept
    {
        String ans = s;
        for (char& i : ans)
            if (i <= 'z' && i >= 'a')
                i -= 32;
        return ans;
    }
}

size_t std::hash<Database::String>::operator()(Database::String const& s) const noexcept {
    return std::hash<std::string>{}(Database::toSTD(s));
}