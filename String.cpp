#include "string.hpp"

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
    delete 
} 
constexpr char String::operator[](size_t index){
    return stringVec[i];
}
constexpr String String::operator()(size_t startIndex, size_t endIndex){
    String s()
}
constexpr String& String::operator+(String s);
constexpr String& String::operator+(char* s);
constexpr String& String::operator=(String s){
    
}
constexpr String& String::operator=(char* s);
constexpr bool String::operator==(String s);
constexpr bool String::operator==(char* s);

constexpr size_t String::length(){
    return stringVec.size();
}

constexpr void String::clear(){
    stringVec.clear();
}