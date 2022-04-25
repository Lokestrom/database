#pragma once

#include <initializer_list>

namespace Database{
    template <typename T>
    class Vector
    {
    private:
        T* arr;
        size_t cur, cap;
        int capIncrease[2] = { 1, 2 };

    public:
        Vector();
        ~Vector();

        T& operator[] (const size_t index);
        Vector<T> operator() (const size_t startIndex, const size_t endIndex);
        Vector<T>& operator= (const Vector<T>& x);
        Vector<T>& operator= (const std::initializer_list<T>& x);
        void pushBack(T val);

        Vector<T> mergeSort();
    }; 
}

#include "Vector.tpp"

