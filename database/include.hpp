/*
Athor: Loke Strøm
Created: 12 apr 2022
*/

#pragma once
#include "Vector.hpp"
#include "String.hpp" 

namespace Database
{
    void onErrorTerminateProgram(bool x);
    void onErrorTerminateWriteFile(bool x);

    bool canStringConvertToNumber(String x);

    //prints error msg to console
    void errorMsg(String where, String ErrorMsg, String ErrorFungtion, Vector<String> ErrorFungtionInput);

    Vector<String> split(String s, String x);
    String splitIndex(String s, String x, int index);

    //template fungtions
    template <typename T>
    bool isString(T x);

    template <typename T>
    String toS(T x);

    template <class T>
    String type_name();

    template <typename T>
    Vector<String> toSVector(Vector<T> x);

    template <typename T>
    Vector<T> mergeSort(Vector<T>& array);

}

#include "include.tpp"