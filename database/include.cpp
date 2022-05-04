/*
Athor: Loke Strøm
Created: 12 apr 2022
*/

#include "include.hpp"

#include "String.hpp"
#include "Vector.hpp"

namespace Database
{
    
    const String splitElement = "|";

    bool terminateProgram = false;
    bool terminateWriteFile = false;
    bool errorHasBeenThrown = false;
    bool NANinData = false;

    void onErrorTerminateProgram(bool x)
    {
        terminateProgram = x;
    }

    void onErrorTerminateWriteFile(bool x)
    {
        terminateWriteFile = x;
    }

    bool canStringConvertToNumber(std::string x)
    {
        for (const char i : x)
            if (i != '0' && i != '1' && i != '2' && i != '3' && i != '4' && i != '5' && i != '6' && i != '7' && i != '8' && i != '9' && i != '.' && i != '-')
                return false;
        return true;
    }

    //prints error msg to console
    void errorMsg(const char* where, const char* ErrorMsg, const char* ErrorFungtion, std::vector<const char*> ErrorFungtionInput)
    {
        errorHasBeenThrown = true;
        std::string error = (std::string)where + ": Error: " + ErrorMsg + ". Error was thrown at " + ErrorFungtion + "(";
        if (ErrorFungtionInput.size() != 0)
        {
            for (int i = 0; i < ErrorFungtionInput.size() - 1; i++)
                error += "\"" + (std::string)ErrorFungtionInput[i] + "\", ";
            error += "\"" + (std::string)ErrorFungtionInput[ErrorFungtionInput.size() - 1] + "\");\n";
        }
        else
            error += "();";
        std::cout << error;
        if (terminateProgram)
        {
            std::exit(1);
        }
    }

    std::vector<std::string> split(std::string s, std::string x)
    {
        std::vector<std::string> splitarr = {};
        size_t pos;

        //findes all the colomn names in the file
        while ((pos = s.find(x)) != std::string::npos)
        {
            splitarr.push_back(s.substr(0, pos));
            s.erase(0, pos + x.length());
        }
        splitarr.push_back(s);
        return splitarr;
    }

    std::string splitIndex(std::string s, std::string x, int index)
    {
        size_t pos;
        std::string produkt = "", startString = s;
        int i = 0;
        s += splitElement;
        //findes all the colomn names in the file
        while (i <= index)
        {
            pos = s.find(x);
            if (pos == -1)
            {
                errorMsg("include.hpp", "Index out of range", "splitIndex", {startString, splitElement, toS(index)});
                return "";
            }
            produkt = (s.substr(0, pos));
            s.erase(0, pos + x.length());
            i++;
        }
        return produkt;
    }
}