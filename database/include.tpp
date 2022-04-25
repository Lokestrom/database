#include <fstream>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <limits>

namespace DatabaseFung{
    template <typename T>
    bool isString(T x)
    {
        return type_name(x) == "std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >";
    }

    template <typename T>
    std::string toS(T x)
    {
        // Create an output string stream
        std::ostringstream streamObj3;
        // Set Fixed -Point Notation
        streamObj3 << std::fixed;
        // Set precision to 2 digits
        streamObj3 << std::setprecision(12);
        //Add double to stream
        streamObj3 << x;
        // Get string from output string stream
        return streamObj3.str();
    }

    template <class T>
    std::string type_name()
    {
        typedef typename std::remove_reference<T>::type TR;
        std::unique_ptr<char, void (*)(void*)> own(
#ifndef _MSC_VER
            abi::__cxa_demangle(typeid(TR).name(), nullptr,
                nullptr, nullptr),
#else
            nullptr,
#endif
            std::free);
        std::string r = own != nullptr ? own.get() : typeid(TR).name();
        if (std::is_const<TR>::value)
            r += " const";
        if (std::is_volatile<TR>::value)
            r += " volatile";
        if (std::is_lvalue_reference<T>::value)
            r += "&";
        else if (std::is_rvalue_reference<T>::value)
            r += "&&";
        return r;
    }

    template <typename T>
    std::vector<std::string> toSVector(std::vector<T> x)
    {
        std::vector<std::string> y = {};
        for (T i : x)
            y.push_back(toS(i));
        return y;
    }

    template <typename T>
    std::vector<T> mergeSort(std::vector<T>& array)
    {
        if (array.size() == 1)
            return array;
        auto splitPoint = array.begin() + array.size() / 2;
        auto begin = array.begin();
        auto end = array.end();
        typename std::vector<T> x(begin, splitPoint), y(splitPoint++, end);
        x = mergeSort(x);
        y = mergeSort(y);
    
        array = {};
        auto xp = 0, yp = 0;
        while (x.size() != xp && y.size() != yp)
        {
            if (x[xp] < y[yp])
            {
                array.push_back(x[xp]);
                xp++;
            }
            else
            {
                array.push_back(y[yp]);
                yp++;
            }
        }
    
        for (auto i = xp; i < x.size(); i++)
        {
            array.push_back(x[i]);
        }
        for (auto i = yp; i < y.size(); i++)
        {
            array.push_back(y[i]);
        }
        return array;
    }
}