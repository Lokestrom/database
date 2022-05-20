#pragma once
#include "Vector.hpp"

namespace Database {
    class String {
    private:
        Vector<char> stringVec;

    public:
        String();
        String(const String& s);
        String(const char* s);
        String(const Vector<char> s);

        constexpr char operator[](const size_t index);
        String operator()(const size_t startIndex, const size_t endIndex);

        constexpr String& operator+=(const String& s);
        constexpr String& operator+=(const char* s);

        const friend String operator+(const String& l, const String& r);
        const friend String operator+(const String& l, const char* r);
        const friend String operator+(const char* l, const String& r);

        constexpr String& operator=(const String& s);
        constexpr String& operator=(const char* s);

        bool operator==(const String s);
        bool operator!=(const String s);

        friend std::ostream& operator<<(std::ostream& output, const String& s);
        friend std::ofstream& operator<<(std::ofstream& output, const String& s);
        friend std::istream& operator>>(std::istream& input, String& s);
        friend std::ifstream& operator>>(std::ifstream& input, String& s);

        constexpr Vector<char> vectorData();
        const char* data();
        const size_t length();
        const void clear();

        const char* begin();
        const char* end();

        const char* begin() const;
        const char* end() const;

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