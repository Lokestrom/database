#pragma once

#include "Vector.hpp"

class String{
private:
    Vector<char>* stringVec;

public:
    String();
    String(String s);
    String(char *s);
    ~String(); 

    constexpr char operator[](size_t index);
    constexpr String operator()(size_t index);

    constexpr String& operator+(String s);
    constexpr String& operator+(char *s);
    constexpr String& operator=(String s);
    constexpr String& operator=(char *s);

    constexpr bool operator==(String s);
    constexpr bool operator==(char *s);

    constexpr size_t length();
    constexpr size_t clear();

};