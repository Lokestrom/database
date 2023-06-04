/*
Athor: Loke Strøm
*/
#pragma once

#include <string>
#include "Vector.hpp"

namespace Database {
    class String {
    private:
        Vector<char> stringVec;
    public:
        constexpr String() noexcept;
        String(const String& s) noexcept;
        String(String&& s) noexcept;
        constexpr String(const char* s) noexcept;
        String(const Vector<char>& v) noexcept;
        String(const std::string& s) noexcept;

        String& operator=(const String& s) noexcept;
        String& operator=(String&& s) noexcept;
        constexpr String& operator=(const char* s) noexcept;
        String& operator=(const std::string& s);
        String& operator=(const Vector<char>& s);
        String& operator=(const std::initializer_list<char>& iList) noexcept;


        //element accses
        constexpr char& operator[](const size_t index) noexcept;
        constexpr char& operator[](const size_t index) const noexcept;

        String operator()(const size_t startIndex, const size_t endIndex) const;

        constexpr char& at(const size_t index);
        constexpr char& at(const size_t index) const;

        const char* cstr() noexcept;
        const char* cstr() const noexcept;

        Vector<char>& vectorData() noexcept;
        Vector<char> vectorData() const noexcept;


        //iterator
        char* begin() noexcept;
        char* begin() const noexcept;

        char* end() noexcept;
        char* end() const noexcept;

        //capacity
        const bool empty() noexcept;

        size_t capacity() noexcept;

        const size_t length() const noexcept;

        constexpr void reserve(const size_t newCapacity) noexcept;

        constexpr void shrinkToFit() noexcept;


        //operations
        String& operator+=(const String s) noexcept;
        constexpr String& operator+=(const char* s) noexcept;

        constexpr void pushBack(const char val) noexcept;

        void insert(const size_t index, const String& s);
        void insert(size_t index, const char* s);
        void insert(size_t index, const char c);
        constexpr void insert(const size_t index, const Vector<char>& vector);
        constexpr void insert(const size_t index, const std::initializer_list<char>& initializerList);

        void popBack();

        void pop(const size_t index);
        void pop(const size_t startIndex, const size_t endIndex);

        const void clear() noexcept;

        const void lower() noexcept;
        const void upper() noexcept;

        //search
        const bool contains(const String& target) noexcept;
        long long binarySearch(const char target) noexcept;
        long long linearSearch(const char target) noexcept;
        constexpr long long linearSearchR(const char target) noexcept;

        //sort
        constexpr void mergeSort() noexcept;
        constexpr void bubbleSort() noexcept;


        const Vector<String> split(const char splitElement) const noexcept;
        const String remove(const char element) const noexcept;

        //non member fungtions
        const friend bool operator==(const String& lhs, const String& rhs) noexcept;
        const friend bool operator!=(const String& lhs, const String& rhs) noexcept;

        const friend String operator+(const String& l, const String& r) noexcept;
        const friend String operator+(const String& l, const char* r) noexcept;
        const friend String operator+(const String& l, const char r) noexcept;
        const friend String operator+(const char* l, const String& r) noexcept;

        friend std::ostream& operator<<(std::ostream& output, const String& s) noexcept;
        friend std::ofstream& operator<<(std::ofstream& output, const String& s) noexcept;
        friend std::istream& operator>>(std::istream& input, String& s) noexcept;
        friend std::ifstream& operator>>(std::ifstream& input, String& s) noexcept;
    };

    //extra String fungtions

    std::string toSTD(const String& s);

    String toS(int x);
    String toS(long x);
    String toS(long long x);
    String toS(unsigned x);
    String toS(unsigned long x);
    String toS(unsigned long long x);
    String toS(double x);
    String toS(long double x);

    int SToi(const String& s);
    long STol(const String& s);
    long long SToll(const String& s);
    unsigned STou(const String& s);
    unsigned long SToul(const String& s);
    unsigned long long SToull(const String& s);
    double STod(const String& s);
    long double STold(const String& s);

    long long substringIndex(const String& s, const String& subS);
    bool canStringConvertToNumber(const String& x);
    bool getline(std::ifstream& file, String& string);

    String lower(const String& s) noexcept;
    String upper(const String& s) noexcept;
}

template<>
struct std::hash<Database::String> {
    size_t operator()(Database::String const& s) const noexcept;
};