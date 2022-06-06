#pragma once

#include "Vector.hpp"

namespace Database {
    class String {
    private:
        Vector<char> stringVec;

        constexpr String errorMsg(const String ErrorMsg, const String fungtion, const Vector<String> fungtionInput, const Vector<String> fungtionInputType) noexcept;
        constexpr String errorMsg(const String ErrorMsg, const String fungtion) noexcept;

    public:
        String() noexcept;
        String(const String& s) noexcept;
        String(const char* s) noexcept;
        String(const Vector<char> s) noexcept;
        String(const std::string) noexcept;

        constexpr char operator[](const size_t index) noexcept;
        constexpr char operator[](const size_t index) const noexcept;
        String operator()(const size_t startIndex, const size_t endIndex);

        constexpr String& operator+=(const String& s) noexcept;
        constexpr String& operator+=(const char* s) noexcept;

        const friend String operator+(const String& l, const String& r) noexcept;
        const friend String operator+(const String& l, const char* r) noexcept;
        const friend String operator+(const char* l, const String& r) noexcept;

        constexpr String& operator=(const String& s) noexcept;
        constexpr String& operator=(const char* s) noexcept;

        bool operator==(const String s) noexcept;
        bool operator!=(const String s) noexcept;

        friend std::ostream& operator<<(std::ostream& output, const String& s);
        friend std::ofstream& operator<<(std::ofstream& output, const String& s);
        friend std::istream& operator>>(std::istream& input, String& s);
        friend std::ifstream& operator>>(std::ifstream& input, String& s);

        constexpr char& at(const size_t index);
        constexpr char& at(const size_t index) const;
           
        constexpr void shrinkToFit() noexcept;
        constexpr void reserve(const size_t newCapacity) noexcept;
        Vector<char> vectorData() noexcept;
        Vector<char> vectorData() const noexcept;
        const char* data() noexcept;
        const char* data() const noexcept;
        const size_t length() const noexcept;
        const void clear() const noexcept;

        const char* begin() noexcept;
        const char* end() noexcept;

        const char* begin() const noexcept;
        const char* end() const noexcept;

        constexpr void pushBack(const char val) noexcept;
        constexpr void popBack();

        constexpr void insert(const size_t index, const String s);
        constexpr void insert(const size_t index, const char* s);
        constexpr void insert(const size_t index, const Vector<char>& vector);
        constexpr void insert(const size_t index, const std::initializer_list<char> initializerList);
        //constexpr void insert(const size_t index, const T arr[]);

        constexpr void pop(const size_t index);
        constexpr void pop(const size_t startIndex, const size_t endIndex);

        constexpr long long binarySerch(const char val) noexcept;
        constexpr long long linearSearch(const char val) noexcept;
        constexpr long long binarySerch(const char val) const noexcept;
        constexpr long long linearSearch(const char val) const noexcept;
    };

    //extra String fungtions

    String toS(int x);
    String toS(long x);
    String toS(long long x);
    String toS(unsigned x);
    String toS(unsigned long x);
    String toS(unsigned long long x);
    String toS(double x);
    String toS(long double x);

    int SToi(String s);
    long STol(String s);
    long long SToll(String s);
    unsigned STou(String s);
    unsigned long SToul(String s);
    unsigned long long SToull(String s);
    double STod(String s);
    long double STold(String s);

    bool canStringConvertToNumber(String x);
}