#pragma once

#include "Vector.hpp"

namespace Database{
    constexpr size_t strlen(char* s){
        char* ptr = s
        size_t count;
        while(prt != '\0'){
            ptr++;
            count;
        }
        return count;
    }

    class String{
    private:
        Vector<char>* stringVec;

    public:
        String();
        String(String s);
        String(char *s);
        ~String(); 

        constexpr char operator[] (size_t index);
        constexpr String operator() (size_t index);

        constexpr String& operator+ (String s);
        constexpr String& operator+ (char *s);
        constexpr String& operator= (String s);
        constexpr String& operator= (char *s);

        constexpr bool operator== (String s);
        constexpr bool operator== (char *s);

        constexpr bool operator!= (String s);
        constexpr bool operator!= (char *s);

        constexpr size_t length();
        constexpr size_t clear();

        constexpr char* begin();
        constexpr char* end();

        constexpr char* begin() const;
        constexpr char* end() const;

    };
};