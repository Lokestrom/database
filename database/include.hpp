/*
Athor: Loke Strøm
Created: 12 apr 2022
*/

#pragma once

#include <fstream>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <limits>

#include <type_traits>
#include <typeinfo>
#ifndef _MSC_VER
#include <cxxabi.h>
#endif
#include <memory>
#include <string>
#include <cstdlib>

namespace Database
{
    void onErrorTerminateProgram(bool x);
    void onErrorTerminateWriteFile(bool x);

    bool canStringConvertToNumber(std::string x);

    //prints error msg to console
    void errorMsg(const char* where, const char* ErrorMsg, const char* ErrorFungtion, std::vector<const char*> ErrorFungtionInput);
    void errorMsgOperator(const char* where, const char* ErrorMsg, const char* ErrorFungtion, const char* );

    std::vector<std::string> split(std::string s, std::string x);
    std::string splitIndex(std::string s, std::string x, int index);

    //template fungtions
    template <typename T>
    bool isString(T x);

    template <typename T>
    std::string toS(T x);

    template <class T>
    std::string type_name();

    template <typename T>
    std::vector<std::string> toSVector(std::vector<T> x);

    template <typename T>
    std::vector<T> mergeSort(std::vector<T>& array);

}

#include "include.tpp"