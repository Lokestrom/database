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
    constexpr String::String() noexcept {
        _arr = new char[3];
        _currentCapacity = 3;
        _currentSize = 1;
        _arr[0] = '\0';
    }
    String::String(const String& s) noexcept {
        _arr = new char[3];
        _currentCapacity = 3;
        _currentSize = 1;
        _arr[0] = '\0';
        *this = s;
    }
    String::String(String&& s) noexcept {
        *this = std::move(s);
    }
    String::String(const char* s) noexcept {
        _arr = new char[3];
        _currentCapacity = 3;
        _currentSize = 1;
        _arr[0] = '\0';
        *this = s;
    }
    String::String(const std::string& s) noexcept {
        _arr = new char[3];
        _currentCapacity = 3;
        _currentSize = 1;
        _arr[0] = '\0';
        *this = s;
    }

    String& String::operator=(const String& s) noexcept {
        this->clear();
        if (this->capacity() < s.length()) {
            this->reserve(s.capacity());
        }
        for (const auto& i : s)
            this->pushBack(i);
        return *this;
    }
    String& String::operator=(String&& s) noexcept {
        _arr = s._arr;
        s._arr = nullptr;
        _currentSize = s.length()+1;
        s._currentSize = 0;
        _currentCapacity = s.capacity()+1;
        s._currentCapacity = 0;

        return *this;
    }
    String& String::operator=(const char* s) noexcept {
        this->clear();
        size_t len = strlen(s);
        if (this->capacity() < len) {
            this->reserve(len);
        }
        if (s == nullptr)
            return *this;
        for (const char* ptr = s; *ptr != '\0'; ptr++)
            this->pushBack(*ptr);
        return *this;
    }
    String& String::operator=(const std::string& s) {
        this->clear();
        for (const char& i : s)
            this->pushBack(i);
        return *this;
    }


    constexpr char& String::operator[](const size_t index) noexcept {
        return _arr[index];
    }
    constexpr char& String::operator[](const size_t index) const noexcept {
        return _arr[index];
    }

    String String::operator()(const size_t startIndex, const size_t endIndex) const {
        if (startIndex >= this->length())
            throw OutOfRange("startIndex out of range");
        if (endIndex > this->length())
            throw OutOfRange("endIndex out of range");
        if (startIndex > endIndex)
            throw OutOfRange("startIndex can't be greater than endIndex");
        String x;
        for (auto i = startIndex; i < endIndex; i++)
            x.pushBack(_arr[i]);
        return x;
    }

    char& String::at(const size_t index) {
        if (index >= this->length())
            throw OutOfRange("index out of range");
        return _arr[index];
    }
    char& String::at(const size_t index) const {
        if (index >= this->length())
            throw OutOfRange("index out of range");
        return _arr[index];
    }

    const char* String::cstr() const noexcept {
        return _arr;
    }

    char* String::begin() const noexcept {
        return _arr;
    }

    char* String::end() const noexcept {
        return &_arr[this->length()];
    }

    const bool String::empty() const noexcept {
        return _currentSize == 0;
    }

    size_t String::capacity() const noexcept {
        return _currentCapacity-1;
    }

    const size_t String::length() const noexcept {
        return _currentSize-1;
    }

    void String::reserve(const size_t newCapacity) {
        if (newCapacity < _currentCapacity) {
            throw LengthError("newCapacity can't be less than currentCapacity");
        }
        char* temp = new char[newCapacity+1];
        for (auto i = 0; i < _currentSize; i++)
            temp[i] = _arr[i];

        delete[] _arr;
        _arr = temp;

        _currentCapacity = newCapacity;
    }
    void String::shrinkToFit() noexcept {
        char* temp = new char[_currentSize];
        _currentCapacity = _currentSize;
        for (auto i = 0; i < _currentSize; i++)
            temp[i] = _arr[i];

        delete[] _arr;
        _arr = temp;
    }

    String& String::operator+=(const String& s) noexcept {
        for (const char& i : s)
            this->pushBack(i);
        return *this;
    }

    constexpr String& String::operator+=(const char* s) noexcept {
        if (s == nullptr)
            return *this;
        for (const char* ptr = s; *ptr != '\0'; ptr++)
            this->pushBack(*ptr);
        return *this;
    }

    void String::pushBack(const char val) noexcept {
        if (this->length() >= this->capacity()) {
            size_t newCap = this->capacity() + (this->capacity() / 2) + 2;
            this->reserve(newCap);
        }
        _arr[this->length()] = val;
        _arr[_currentSize] = '\0';
        _currentSize++;
    }

    void String::insert(const size_t index, const String& s) {
        for (auto it = s.end() - 1; it != s.begin() - 1; it--)
            insert(index, *it);
    }
    void String::insert(size_t index, const char* s) {
        if (index >= this->length())
            throw OutOfRange("index out of range");
        for (const char* ptr = s; *ptr != '\0'; ptr++)
            this->insert(index++, *ptr);
    }
    void String::insert(size_t index, char c) {
        if (index > this->length())
            throw OutOfRange("Index out of range");

        _currentSize++;
        if (this->length() > this->capacity()) {
            size_t newCap = this->capacity() + (this->capacity() / 2) + 2;
            this->reserve(newCap);
        }
        char lastVal;
        for (auto i = index; i < this->length(); i++) {
            lastVal = _arr[i];
            _arr[i] = c;
            c = lastVal;
        }
        _arr[_currentSize] = '\0';
    }

    void String::popBack() {
        if (this->length() == 0)
            throw LengthError("Can't popBack on empty Vector");

        _currentSize--;
    }

    void String::pop(const size_t index) {
        if (index >= this->length())
            throw OutOfRange("Index out of range");
        _currentSize--;
        for (auto i = index; i < this->length(); i++)
            _arr[i] = _arr[i + 1];
    }
    void String::pop(const size_t startIndex, const size_t endIndex) {
        if (startIndex >= this->length())
            throw OutOfRange("startIndex out of range");
        if (endIndex > this->length())
            throw OutOfRange("endIndex out of range");
        if (startIndex > endIndex)
            throw OutOfRange("startIndex can't be greater than endIndex");

        size_t diff = endIndex - startIndex;
        _currentSize -= diff;
        for (auto i = startIndex; i < this->length(); i++)
            _arr[i] = _arr[i + diff];
    }

    const void String::clear() noexcept {
        _currentSize = 1;
        _arr[0] = '\0';
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
        long long low = 0;
        long long high = this->length() - 1;
        long long mid;

        while (low <= high)
        {
            mid = (low + high) / 2;

            if (_arr[mid] == target)
                return mid;
            else if (_arr[mid] > target)
                high = mid - 1;
            else
                low = mid + 1;
        }
        return -1;
    }

    long long String::linearSearch(const char target) noexcept {
        for (auto i = 0; i < this->length(); i++)
            if (_arr[i] == target)
                return i;
        return -1;
    }
    long long String::linearSearchR(const char target) noexcept {
        for (long long i = this->length() - 1; i > -1; i--)
            if (_arr[i] == target)
                return i;
        return -1;
    }

    void String::mergeSort() noexcept {
        if (this->length() == 1)
            return;

        String start;
        start = this->operator()(0, this->length() / 2);
        String end;
        end = this->operator()(this->length() / 2, this->length());

        start.mergeSort();
        end.mergeSort();

        clear();

        size_t startPos = 0, endPos = 0;

        while (startPos != start.length() && endPos != end.length()) {
            if (start[startPos] < end[endPos]) {
                pushBack(start[startPos]);
                startPos++;
            }
            else {
                pushBack(end[endPos]);
                endPos++;
            }
        }

        for (;startPos != start.length(); startPos++)
            pushBack(start[startPos]);
        for (;endPos != end.length(); endPos++)
            pushBack(end[endPos]);

        return;
    }

    void String::bubbleSort() noexcept {
        char temp;
        for (auto i = 0; i < this->length(); i++)
        {
            for (auto j = 0; j < this->length() - i - 1; j++)
            {
                if (_arr[j] > _arr[j + 1])
                {
                    temp = _arr[j + 1];
                    _arr[j + 1] = _arr[j];
                    _arr[j] = temp;
                }
            }
        }
        return;
    }

    const Vector<String> String::split(const char splitElement) const noexcept {
        Vector<String> splitStrings;
        String currentString;
        for (size_t i = 0; i < this->length(); i++) {
            if (_arr[i] == splitElement && !currentString.empty()) {
                splitStrings.pushBack(currentString);
                currentString.clear();
            }
            else {
                currentString.pushBack(_arr[i]);
            }
        }
        splitStrings.pushBack(currentString);
        return splitStrings;
    }

    const void String::remove(const char element) noexcept {
        String removedString;
        for (size_t i = 0; i < this->length(); i++)
            if (_arr[i] != element)
                removedString.pushBack(_arr[i]);
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
        if (lsh.length() != rsh.length())
            return false;

        for (auto i = 0; i < lsh.length(); i++)
            if (lsh[i] != rsh[i])
                return false;
        return true;
    }
    const bool operator!=(const String& lsh, const String& rsh) noexcept {
        return !(lsh == rsh);
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