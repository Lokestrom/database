#include "string.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include "Exception.hpp"
#include "Vector.hpp"

namespace Database {

    constexpr String String::errorMsg(const String ErrorMsg, const String fungtion, const Vector<String> fungtionInput, const Vector<String> fungtionInputType) noexcept const {
        String x;
        x = "String: Error: " + ErrorMsg + ". Error was thrown at " + fungtion + "( ";
        for (auto i = 0; i < fungtionInputType.size() || fungtionInput.size(); i++)
            x += (i > fungtionInputType.size())
            ? "(" + (String)fungtionInputType[i] + "), "
            : "(" + (String)fungtionInputType[i] + ") " + (String)fungtionInput[i] + ", ";

        x.pop_back();
        x.pop_back();
        x += " );\n";
        return x;
    }


    constexpr String::String() noexcept {}
    constexpr String::String(const String& s) noexcept{
        *this = s;
    }

    constexpr String::String(const char* s) noexcept{
        *this = s;
    }

    constexpr String::String(const Vector<char> s) noexcept{
        stringVec = s;
    }

    constexpr ::String(const std::string s)noexcept{
        for (const char& i : s)
            stringVec.pushBack(i);
    }

    constexpr char String::operator[](const size_t index) noexcept{
        return stringVec[index];
    }

    String String::operator()(const size_t startIndex, const size_t endIndex) {
        if (startIndex >= stringVec.size())
            throw Exception(errorMsg("startIndex out of range", "operator()", { to_string(startIndex), to_string(endIndex) }, { "const size_t", "const size_t" }));
        if (endIndex > stringVec.size())
            throw Exception(errorMsg("endIndex out of range", "operator()", { to_string(startIndex), to_string(endIndex) }, { "const size_t", "const size_t" }));
        if (startIndex > endIndex)
            throw Exception(errorMsg("startIndex is greater than endIndex", "operator()", { to_string(startIndex), to_string(endIndex) }, { "const size_t", "const size_t" }));
        return String(stringVec(startIndex, endIndex));
    }

    constexpr String& String::operator+=(const String& s)noexcept {
        stringVec.insert(stringVec.size(), s.stringVec);
        return *this;
    }

    constexpr String& String::operator+=(const char* s) noexcept{
        for (const char* ptr = s; *ptr != '\0'; ptr++)
            stringVec.pushBack(*ptr);
        return *this;
    }

    const String operator+(const String& l, const String& r) {
        String s(l);
        s += r;
        return s;
    }

    const String operator+(const String& l, const char* r) noexcept{
        String s(l);
        s += r;
        return s;
    }

    const String operator+(const char* l, const String& r) noexcept{
        String s(l);
        s += r;
        return s;
    }

    constexpr String& String::operator=(const String& s) noexcept{
        stringVec = s.stringVec;
        return *this;
    }

    constexpr String& String::operator=(const char* s) noexcept{
        stringVec.clear();
        for (const char* ptr = s; *ptr != '\0'; ptr++)
            stringVec.pushBack(*ptr);
        return *this;
    }

    bool String::operator==(const String s) noexcept{
        return stringVec == s.stringVec;
    }

    bool String::operator!=(const String s) noexcept{
        return stringVec != s.stringVec;
    }

    std::ostream& operator<<(std::ostream& output, const String& s) noexcept{
        for (const char& i : s)
            output << i;
        return output;
    }

    std::ofstream& operator<<(std::ofstream& output, const String& s) noexcept{
        for (const char& i : s)
            output << i;
        return output;
    }

    std::istream& operator>>(std::istream& input, String& s) noexcept{ 
        char* buff = new char[1000];
        input.getline(buff, 1000);
        s = buff;
        delete[] buff;
        return input;
    }

    std::ifstream& operator>>(std::ifstream& input, String& s) noexcept{
        char* buff = new char[1000];
        input.getline(buff, 1000);
        s = buff;
        delete[] buff;
        return input;
    }

    Vector<char> String::vectorData() noexcept{
        return stringVec;
    }

    const char* String::data() noexcept{
        return stringVec.data();
    }

    const size_t String::length() noexcept{
        return stringVec.size();
    }

    const void String::clear() noexcept{
        stringVec.clear();
    }

    const char* String::begin() noexcept{
        return stringVec.begin();
    }

    const char* String::end() noexcept{
        return stringVec.end();
    }

    const char* String::begin() const noexcept{
        return stringVec.begin();
    }

    const char* String::end() const noexcept{
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