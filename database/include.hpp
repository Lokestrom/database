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
}

#include "include.tpp"