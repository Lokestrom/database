#include "string.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include "Exception.hpp"
#include "Vector.hpp"

namespace Database {

    String String::errorMsg(const String ErrorMsg, const String fungtion, const Vector<String> fungtionInput, const Vector<String> fungtionInputType) const noexcept {
        String x;
        x = "String: Error: " + ErrorMsg + ". Error was thrown at " + fungtion + "( ";
        for (auto i = 0; i < fungtionInputType.size() || i < fungtionInput.size(); i++)
            x += (i > fungtionInputType.size())
            ? "(" + (String)fungtionInputType[i] + "), "
            : "(" + (String)fungtionInputType[i] + ") " + (String)fungtionInput[i] + ", ";

        x.popBack();
        x.popBack();
        x += " );\n";
        return x;
    }

    String String::errorMsg(const String ErrorMsg, const String fungtion) const noexcept {
        String s;
        s = "String: Error: " + ErrorMsg + ". Error was thrown at " + fungtion + "();\n";
        return s;
    }


    constexpr String::String() noexcept {}
    constexpr String::String(const String& s) noexcept {
        *this = s;
    }

    constexpr String::String(const char* s) noexcept {
        *this = s;
    }

    String::String(const Vector<char> s) noexcept {
        stringVec = s;
    }

    constexpr String::String(const std::string s) noexcept {
        for (const char& i : s)
            stringVec.pushBack(i);
    }

    constexpr char String::operator[](const size_t index) noexcept {
        return stringVec[index];
    }

    String String::operator()(const size_t startIndex, const size_t endIndex) {
        if (startIndex >= stringVec.size())
            throw OutOfRange(errorMsg("startIndex out of range", "operator()", { to_string(startIndex), to_string(endIndex) }, { "const size_t", "const size_t" }));
        if (endIndex > stringVec.size())
            throw OutOfRange(errorMsg("endIndex out of range", "operator()", { to_string(startIndex), to_string(endIndex) }, { "const size_t", "const size_t" }));
        if (startIndex > endIndex)
            throw OutOfRange(errorMsg("startIndex is greater than endIndex", "operator()", { to_string(startIndex), to_string(endIndex) }, { "const size_t", "const size_t" }));
        return String(stringVec(startIndex, endIndex));
    }

    constexpr String& String::operator+=(const String& s) noexcept {
        stringVec.insert(stringVec.size(), s.stringVec);
        return *this;
    }

    constexpr String& String::operator+=(const char* s) noexcept {
        for (const char* ptr = s; *ptr != '\0'; ptr++)
            stringVec.pushBack(*ptr);
        return *this;
    }

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

    const String operator+(const char* l, const String& r) noexcept {
        String s(l);
        s += r;
        return s;
    }

    constexpr String& String::operator=(const String& s) noexcept {
        stringVec = s.stringVec;
        return *this;
    }

    constexpr String& String::operator=(const char* s) noexcept {
        stringVec.clear();
        for (const char* ptr = s; *ptr != '\0'; ptr++)
            stringVec.pushBack(*ptr);
        return *this;
    }

    bool String::operator==(const String s) noexcept {
        return stringVec == s.stringVec;
    }

    bool String::operator!=(const String s) noexcept {
        return stringVec != s.stringVec;
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

    constexpr char& String::at(const size_t index) {
        if (index >= stringVec.size())
            throw OutOfRange(errorMsg("Index out of range", "at", { toS(index) }, { "size_t" }));
        return stringVec[index];
    }
    constexpr char& String::at(const size_t index) const {
        if (index >= stringVec.size())
            throw OutOfRange(errorMsg("Index out of range", "at", { toS(index) }, { "size_t" }));
        return stringVec[index];
    }

    constexpr void String::shrinkToFit() noexcept {
        stringVec.shrinkToFit();
    }
    constexpr void String::reserve(const size_t newCapacity) noexcept {
        stringVec.reserve(newCapacity);
    }

    Vector<char> String::vectorData() noexcept {
        return stringVec;
    }

    Vector<char> String::vectorData() const noexcept {
        return stringVec;
    }

    const char* String::data() noexcept {
        return stringVec.data();
    }

    const char* String::data() const noexcept {
        return stringVec.data();
    }

    const size_t String::length() const noexcept {
        return stringVec.size();
    }

    const void String::clear() noexcept {
        stringVec.clear();
    }

    char* String::begin() noexcept {
        return stringVec.begin();
    }

    char* String::end() noexcept {
        return stringVec.end();
    }

    char* String::begin() const noexcept {
        return stringVec.begin();
    }

    char* String::end() const noexcept {
        return  stringVec.end();
    }

    constexpr void String::pushBack(const char val) noexcept {
        stringVec.pushBack(val);
    }

    constexpr void String::popBack() {
        if (stringVec.size() == 0)
            throw LengthError(errorMsg("popBack on empty String", "popBack"));
        stringVec.popBack();
    }

    void String::insert(const size_t index, const String s) {
        if (index > stringVec.size())
            throw OutOfRange(errorMsg("Index out of range", "insert", { toS(index), s }, { "const size_t", "const String" }));
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

    constexpr void String::pop(const size_t index) {
        stringVec.pop(index);
    }
    constexpr void String::pop(const size_t startIndex, const size_t endIndex) {
        stringVec.pop(startIndex, endIndex);
    }

    constexpr long long String::binarySerch(const char val) const noexcept {
        return stringVec.binarySerch(val);
    }

    constexpr long long String::linearSearch(const char val) const noexcept {
        return linearSearch(val);
    }

    constexpr void String::mergeSort() noexcept {
        stringVec.mergeSort();
    }
    constexpr void String::bubbleSort() noexcept {
        stringVec.bubbleSort();
    }

    const String String::lower() {
        String s(*this);

        for (char& i : s)
            if (i <= 'Z' && i >= 'A')
                i += 32;
        
        return s;
    }
    const String String::upper() {
        String s(*this);

        for (char& i : s)
            if (i <= 'z' && i >= 'a')
                i -= 32;

        return s;
    }

    //
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

    bool substringExsist(String s, String subS) {
        bool isSubS = false;
        for (auto i = 0; i < s.length(); i++) {
            if (s[i] == subS[0]) {
                isSubS = true;
                for (auto j = 0; j < subS.length(); j++)
                    if (s[j + i] != subS[j])
                        isSubS = false;
            }
            if (isSubS)
                return true;
        }
        return false;
    }

    bool canStringConvertToNumber(const String s) {
        for (const char& i : s)
            if (i != '0' && i != '1' && i != '2' && i != '3' && i != '4' && i != '5' && i != '6' && i != '7' && i != '8' && i != '9' && i != '.' && i != '-')
                return false;
        return true;
    }
}