/*
Athor: Loke Strøm
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

    constexpr String::String(const char* s) noexcept {
        *this = s;
    }

    String::String(Vector<char> v) noexcept {
        stringVec = v;
    }

    String::String(const std::string& s) noexcept {
        *this = s;
    }

    constexpr char& String::operator[](const size_t index) noexcept {
        return stringVec[index];
    }

    constexpr char& String::operator[](const size_t index) const noexcept {
        return stringVec[index];
    }

    String String::operator()(const size_t startIndex, const size_t endIndex){
        if (startIndex >= stringVec.size())
            throw OutOfRange("startIndex out of range");
        if (endIndex > stringVec.size())
            throw OutOfRange("endIndex out of range");
        if (startIndex > endIndex)
            throw OutOfRange("startIndex can't be greater than endIndex");
        return String(stringVec(startIndex, endIndex));
    }

    //operator+=
    String& String::operator+=(const String s) noexcept {
        stringVec.insert(stringVec.size(), s.stringVec);
        return *this;
    }
    constexpr String& String::operator+=(const char* s) noexcept {
        for (const char* ptr = s; *ptr != '\0'; ptr++)
            stringVec.pushBack(*ptr);
        return *this;
    }

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

    //operator=
    String& String::operator=(const String& s) noexcept {
        stringVec = s.stringVec;
        return *this;
    }
    constexpr String& String::operator=(const char* s) noexcept {
        stringVec.clear();
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
    
    //
    const bool operator==(const String& lsh, const String& rsh) noexcept {
        return lsh.stringVec == rsh.stringVec;
    }
    const bool operator!=(const String& lsh, const String& rsh) noexcept {
        return lsh.stringVec == rsh.stringVec;
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
        char* buff = new char[input.gcount()];
        input.getline(buff, input.gcount());
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

    //at
    constexpr char& String::at(const size_t index) {
        if (index >= stringVec.size())
            throw OutOfRange("Index out of range");
        return stringVec[index];
    }
    constexpr char& String::at(const size_t index) const {
        if (index >= stringVec.size())
            throw OutOfRange("Index out of range");
        return stringVec[index];
    }

    //shrinkToFit
    constexpr void String::shrinkToFit() noexcept {
        stringVec.shrinkToFit();
    }

    //reserve
    constexpr void String::reserve(const size_t newCapacity) noexcept {
        stringVec.reserve(newCapacity);
    }

    //vectorData
    Vector<char>& String::vectorData() noexcept {
        return stringVec;
    }
    Vector<char> String::vectorData() const noexcept {
        return stringVec;
    }

    //data
    const char* String::cstr() noexcept {
        return stringVec.data();
    }
    const char* String::cstr() const noexcept {
        return stringVec.data();
    }

    //length
    const size_t String::length() const noexcept {
        return stringVec.size();
    }

    //clear
    const void String::clear() noexcept {
        stringVec.clear();
    }

    const bool String::empty() noexcept {
        if (stringVec.size() == 0)
            return true;
        return false;
    }

    //begin
    char* String::begin() noexcept {
        return stringVec.begin();
    }
    char* String::begin() const noexcept {
        return stringVec.begin();
    }

    //end
    char* String::end() const noexcept {
        return  stringVec.end();
    }
    char* String::end() noexcept {
        return stringVec.end();
    }

    //pushBack
    constexpr void String::pushBack(const char val) noexcept {
        stringVec.pushBack(val);
    }

    //popBack
    constexpr void String::popBack() {
        if (stringVec.size() == 0)
            throw LengthError("popBack on empty String");
        stringVec.popBack();
    }

    //insert
    void String::insert(const size_t index, const String s) {
        if (index > stringVec.size())
            throw OutOfRange("Index out of range");
        stringVec.insert(index, s.stringVec);
    }
    void String::insert(const size_t index, const char* s) {
        insert(index, String(s));
    }
    constexpr void String::insert(const size_t index, const Vector<char>& vector) {
        stringVec.insert(index, vector);
    }
    constexpr void String::insert(const size_t index, const std::initializer_list<char> initializerList) {
        stringVec.insert(index, initializerList);
    }

    //pop
    constexpr void String::pop(const size_t index) {
        stringVec.pop(index);
    }
    constexpr void String::pop(const size_t startIndex, const size_t endIndex) {
        stringVec.pop(startIndex, endIndex);
    }

    //search
    const bool String::contains(const String target) noexcept {
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

    constexpr long long String::binarySerch(const char target) const noexcept {
        return stringVec.binarySerch(target);
    }
    constexpr long long String::linearSearch(const char target) const noexcept {
        return stringVec.linearSearch(target);
    }

    constexpr long long String::linearSearchR(const char target) const noexcept {
        return stringVec.linearSearchR(target);
    }

    //sort
    constexpr void String::mergeSort() noexcept {
        stringVec.mergeSort();
    }
    constexpr void String::bubbleSort() noexcept {
        stringVec.bubbleSort();
    }

    //lower
    const void String::lower() noexcept {
        for (char& i : *this)
            if (i <= 'Z' && i >= 'A')
                i += 32;
    }

    //upper
    const void String::upper() noexcept {
        for (char& i : *this)
            if (i <= 'z' && i >= 'a')
                i -= 32;
    }

    const Vector<String> String::split(const char splitElement) const noexcept {
        Vector<String> v;
        String s = "";

        for (const char& c : *this) {
            if (splitElement == c) {
                v.pushBack(s);
                s = "";
            }
            else {
                s.pushBack(c);
            }
        }
        if(!s.empty())
            v.pushBack(s);
        return v;
    }

    //tos
    String toS(const int x) {
        std::stringstream ss;
        String s;
        ss << x;
        ss >> s;
        return s;
    }
    String toS(const long x) {
        std::stringstream ss;
        String s;
        ss << x;
        ss >> s;
        return s;
    }
    String toS(const long long x){
        std::stringstream ss;
        String s;
        ss << x;
        ss >> s;
        return s;
    }
    String toS(const unsigned x){
        std::stringstream ss;
        String s;
        ss << x;
        ss >> s;
        return s;
    }
    String toS(const unsigned long x){
        std::stringstream ss;
        String s;
        ss << x;
        ss >> s;
        return s;
    }
    String toS(const unsigned long long x){
        std::stringstream ss;
        String s;
        ss << x;
        ss >> s;
        return s;
    }
    String toS(const double x) {
        std::stringstream ss;
        String s;
        ss << x;
        ss >> s;
        return s;
    }
    String toS(const long double x) {
        std::stringstream ss;
        String s;
        ss << x;
        ss >> s;
        return s;
    }

    std::string toSTD(String s) {
        std::string r;
        r.reserve(s.length());
        for (const char& c : s)
            r.push_back(c);
        return r;
    }

    //to number
    int SToi(const String s) {
        std::stringstream ss;
        int x;
        ss << s;
        ss >> x;
        return x;
    }
    long STol(const String s) {
        std::stringstream ss;
        long x;
        ss << s;
        ss >> x;
        return x;
    }
    long long SToll(const String s) {
        std::stringstream ss;
        long long x;
        ss << s;
        ss >> x;
        return x;
    }
    unsigned STou(const String s) {
        std::stringstream ss;
        unsigned x;
        ss << s;
        ss >> x;
        return x;
    }
    unsigned long SToul(const String s) {
        std::stringstream ss;
        unsigned long x;
        ss << s;
        ss >> x;
        return x;
    }
    unsigned long long SToull(const String s){
        std::stringstream ss;
        unsigned long long x;
        ss << s;
        ss >> x;
        return x;
    }
    double STod(const String s){
        std::stringstream ss;
        double x;
        ss << s;
        ss >> x;
        return x;
    }
    long double STold(const String s){
        std::stringstream ss;
        long double x;
        ss << s;
        ss >> x;
        return x;
    }

    //subStringIndex
    long long substringIndex(String s, String subS) {
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

    bool canStringConvertToNumber(const String s) {
        for (const char& i : s)
            if (i != '0' && i != '1' && i != '2' && i != '3' && i != '4' && i != '5' && i != '6' && i != '7' && i != '8' && i != '9' && i != '.' && i != '-')
                return false;
        return true;
    }

    bool getline(std::ifstream *file, String& string)
    {
        if (file->eof())
            return false;
        std::string text;
        std::getline(*file, text);
        string = text;
        return true;
    }
}

size_t std::hash<Database::String>::operator()(Database::String const& s) const noexcept {
    return std::hash<std::string>{}(Database::toSTD(s));
}