#include "string.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include "Vector.hpp"

namespace Database {

    constexpr void String::errorMsg(const String ErrorMsg, const String fungtion, const Vector<String> fungtionInput, const Vector<String> fungtionInputType) {
        std::cout << "Vector<" << typeOf<T>() << ">: Error: " << ErrorMsg << ". Error was thrown at " << fungtion << "( ";
        for (const auto& i : fungtionInput)
            std::cout << "(" << fungtionInputType[i] << ") " << fungtionInput[i] <<  ", ";

        std::cout << "\b\b );\n"
        std::exit(1);
    }

    constexpr void String::errorMsg(const String ErrorMsg, const String fungtion) {
        std::cout << "Vector<" << typeOf<T>() << ">: Error: " << ErrorMsg << ". Error was thrown at " << fungtion << "( );\n";
        std::exit(1);
    }

    String::String() {}
    String::String(const String& s) {
        *this = s;
    }

    String::String(const char* s) {
        *this = s;
    }

    String::String(const Vector<char> s) {
        stringVec = s;
    }

    Stirng::String(const std::string s){
        for(const char& : s)
    }

    constexpr char String::operator[](const size_t index) {
        if(index >= stringVec.size())
            errorMsg("Index out of range",)
        return stringVec[index];
    }

    String String::operator()(const size_t startIndex, const size_t endIndex) {
        return String(stringVec(startIndex, endIndex));
    }

    constexpr String& String::operator+=(const String& s) {
        stringVec.insert(stringVec.size(), s.stringVec);
        return *this;
    }

    constexpr String& String::operator+=(const char* s) {
        for (const char* ptr = s; *ptr != '\0'; ptr++)
            stringVec.pushBack(*ptr);
        return *this;
    }

    const String operator+(const String& l, const String& r) {
        String s(l);
        s += r;
        return s;
    }

    const String operator+(const String& l, const char* r) {
        String s(l);
        s += r;
        return s;
    }

    const String operator+(const char* l, const String& r) {
        String s(l);
        s += r;
        return s;
    }

    constexpr String& String::operator=(const String& s) {
        stringVec = s.stringVec;
        return *this;
    }

    constexpr String& String::operator=(const char* s) {
        stringVec.clear();
        for (const char* ptr = s; *ptr != '\0'; ptr++)
            stringVec.pushBack(*ptr);
        return *this;
    }

    bool String::operator==(const String s) {
        return stringVec == s.stringVec;
    }

    bool String::operator!=(const String s) {
        return stringVec != s.stringVec;
    }

    std::ostream& operator<<(std::ostream& output, const String& s) {
        for (const char& i : s)
            output << i;
        return output;
    }

    std::ofstream& operator<<(std::ofstream& output, const String& s) {
        for (const char& i : s)
            output << i;
        return output;
    }

    std::istream& operator>>(std::istream& input, String& s) { 
        char* buff = new char[1000];
        input.getline(buff, 1000);
        s = buff;
        delete[] buff;
        return input;
    }

    std::ifstream& operator>>(std::ifstream& input, String& s) {
        char* buff = new char[1000];
        input.getline(buff, 1000);
        s = buff;
        delete[] buff;
        return input;
    }

    Vector<char> String::vectorData() {
        return stringVec;
    }

    const char* String::data() {
        return stringVec.data();
    }

    const size_t String::length() {
        return stringVec.size();
    }

    const void String::clear() {
        stringVec.clear();
    }

    const char* String::begin() {
        return stringVec.begin();
    }

    const char* String::end() {
        return stringVec.end();
    }

    const char* String::begin() const {
        return stringVec.begin();
    }

    const char* String::end() const {
        return  stringVec.end();
    }

    //
    String toS(int x) {
        std::stringstream ss;
        String s;
        ss << x;
        ss >> s;
        return s;
    }

    String toS(long x) {
        std::stringstream ss;
        String s;
        ss << x;
        ss >> s;
        return s;
    }

    String toS(long long x){
        std::stringstream ss;
        String s;
        ss << x;
        ss >> s;
        return s;
    }

    String toS(unsigned x){
        std::stringstream ss;
        String s;
        ss << x;
        ss >> s;
        return s;
    }

    String toS(unsigned long x){
        std::stringstream ss;
        String s;
        ss << x;
        ss >> s;
        return s;
    }

    String toS(unsigned long long x){
        std::stringstream ss;
        String s;
        ss << x;
        ss >> s;
        return s;
    }

    String toS(double x) {
        std::stringstream ss;
        String s;
        ss << x;
        ss >> s;
        return s;
    }

    String toS(long double x) {
        std::stringstream ss;
        String s;
        ss << x;
        ss >> s;
        return s;
    }

    int SToi(String s) {
        std::stringstream ss;
        int x;
        ss << s;
        ss >> x;
        return x;
    }
     
    long STol(String s) {
        std::stringstream ss;
        long x;
        ss << s;
        ss >> x;
        return x;
    }

    long long SToll(String s) {
        std::stringstream ss;
        long long x;
        ss << s;
        ss >> x;
        return x;
    }

    unsigned STou(String s) {
        std::stringstream ss;
        unsigned x;
        ss << s;
        ss >> x;
        return x;
    }

    unsigned long SToul(String s) {
        std::stringstream ss;
        unsigned long x;
        ss << s;
        ss >> x;
        return x;
    }

    unsigned long long SToull(String s){
        std::stringstream ss;
        unsigned long long x;
        ss << s;
        ss >> x;
        return x;
    }

    double STod(String s){
        std::stringstream ss;
        double x;
        ss << s;
        ss >> x;
        return x;
    }

    long double STold(String s){
        std::stringstream ss;
        long double x;
        ss << s;
        ss >> x;
        return x;
    }

    bool canStringConvertToNumber(String x) {
        for (const char& i : x)
            if (i != '0' && i != '1' && i != '2' && i != '3' && i != '4' && i != '5' && i != '6' && i != '7' && i != '8' && i != '9' && i != '.' && i != '-')
                return false;
        return true;
    }
}