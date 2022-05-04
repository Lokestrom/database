#include "string.hpp"

#include "Vector.hpp"

namespace Database{
    String::String(){
        stringVec = new Vector<char>();
    }

    String::String(String s){
        stringVec = new Vector<char>(s.length());
        *this = s;
    }

    String::String(char* s){
        stringVec = new Vector<char>();
        *this = s;
    }

    String::String(const size_t capacity){
        stringVec = new Vector<char>(capacity);
    }

    String::~String(){
        delete stringVec;
    }

    constexpr char String::operator[] (size_t index){
        return stringVec[i];
    }

    constexpr String String::operator() (size_t startIndex, size_t endIndex){
        String s(endIndex-startIndex);
        for(auto i = startIndex; i < endIndex; i++)
            s.stringVec[i-startIndex] = stringVec[i];

        return s;
    }

    constexpr String& String::operator+ (String s){
        for(char& i : s)
            stringVec.pushBack(i);

        return *this
    }
    constexpr String& String::operator+ (char* s){
        for(char* ptr = s; *ptr != '\0'; ptr++)
            stringVec.pushBack(*ptr);

        return *this;
    }
    constexpr String& String::operator= (String s){
        stringVec = new Vector<char>(s);
    }

    constexpr String& String::operator= (char* s){
        size_t sLength = strlen(s);
        if(stringVec.capacity < stringVec.size() + sLength)
            stringVec.reserve(stringVec.size() + s);

        for(auto i = 0; s[i] != '\0'; i++)
            stringVec.pushBack(s[i]);
        
        return *this;
    }

    constexpr bool String::operator== (String s){
        if(stringVec.size() != s.length())
            return false;

        for(auto i = 0; i < s.length(); i++)
            if(s.stringVec[i] != stringVec[i])
                return false;

        return true;
    }

    constexpr bool String::operator== (char* s){
        for(auto i = 0; i < stringVec.size(); i++)
            if(s[i] != stringVec[i])
                return false;

        return true;    
    }

    constexpr bool String::operator!= (String s){
        return !(*this = s);
    }

    constexpr bool String::operator!= (char *s){
        return !(*this = s);
    }

    constexpr size_t String::length(){
        return stringVec.size();
    }

    constexpr void String::clear(){
        stringVec.clear();
    }

    constexpr char* String::begin(){
        return stringVec.begin();
    }

    constexpr char* String::end(){
        return stringVec.end();
    }

    constexpr char* String::begin() const{
        return stringVec.begin();
    }

    constexpr char* String::end() const{
        return stringVec.end();
    }
};