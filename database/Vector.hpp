#pragma once

namespace Database{
    template <typename T>
    class Vector
    {
    private:
        T* arr;
        int cur, cap, capIncrease[2] = [1, 2];

    public:
        Vector();
        ~Vector();

        T operator[](int i);
        void operator = (const Vector<T> x);
        void pushBack(T val);
    }; 
}

#include "Vector.tpp"

