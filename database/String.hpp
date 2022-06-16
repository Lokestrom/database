#pragma once

#include "Vector.hpp"

namespace Database {
    class String {
    private:
        Vector<char> stringVec;

        String errorMsg(const String ErrorMsg, const String fungtion, const Vector<String> fungtionInput, const Vector<String> fungtionInputType) const noexcept;
        String errorMsg(const String ErrorMsg, const String fungtion) const noexcept;

    public:
        constexpr String() noexcept;
        constexpr String(const String& s) noexcept;
        constexpr String(const char* s) noexcept;
        String(const Vector<char>& v) noexcept;
        constexpr String(const std::string& s) noexcept;

        constexpr char& operator[](const size_t index) noexcept;
        constexpr char& operator[](const size_t index) const noexcept;
        String operator()(const size_t startIndex, const size_t endIndex);

        constexpr String& operator+=(const String& s) noexcept;
        constexpr String& operator+=(const char* s) noexcept;

        const friend String operator+(const String& l, const String& r) noexcept;
        const friend String operator+(const String& l, const char* r) noexcept;
        const friend String operator+(const char* l, const String& r) noexcept;

        constexpr String& operator=(const String& s) noexcept;
        constexpr String& operator=(const char* s) noexcept;
        constexpr String& operator=(const std::string& s) noexcept;
        constexpr String& operator=(const Vector<char>& s) noexcept;
        constexpr String& operator=(const std::initializer_list<char>& iList) noexcept;

        bool operator==(const String s) noexcept;
        bool operator!=(const String s) noexcept;

        friend std::ostream& operator<<(std::ostream& output, const String& s) noexcept;
        friend std::ofstream& operator<<(std::ofstream& output, const String& s) noexcept;
        friend std::istream& operator>>(std::istream& input, String& s) noexcept;
        friend std::ifstream& operator>>(std::ifstream& input, String& s) noexcept;

        constexpr char& at(const size_t index);
        constexpr char& at(const size_t index) const;
           
        constexpr void shrinkToFit() noexcept;
        constexpr void reserve(const size_t newCapacity) noexcept;
        Vector<char>& vectorData() noexcept;
        Vector<char>& vectorData() const noexcept;
        const char* data() noexcept;
        const char* data() const noexcept;
        const size_t length() const noexcept;
        const void clear() noexcept;

        char* begin() noexcept;
        char* end() noexcept;

        char* begin() const noexcept;
        char* end() const noexcept;

        constexpr void pushBack(const char val) noexcept;
        constexpr void popBack();

        void insert(const size_t index, const String s);
        void insert(const size_t index, const char* s);
        constexpr void insert(const size_t index, const Vector<char>& vector);
        constexpr void insert(const size_t index, const std::initializer_list<char> initializerList);

        constexpr void pop(const size_t index);
        constexpr void pop(const size_t startIndex, const size_t endIndex);

        constexpr long long binarySerch(const char val) const noexcept;
        constexpr long long linearSearch(const char val) const noexcept;

        constexpr void mergeSort() noexcept;
        constexpr void bubbleSort() noexcept;

        const String lower();
        const String upper();
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

    long long substringIndex(const String s, const String subS);
    bool substringExsist(String s, String subS);
    bool canStringConvertToNumber(String x);
}