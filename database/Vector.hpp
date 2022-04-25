#pragma once

#include <initializer_list>

namespace Database{
    template <typename T>
    class Vector
    {
    private:
        T* arr = nullptr;
        size_t cur = 0, cap = 0;
        int capIncrease[2] = { 1, 2 };

    public:

        constexpr void changeCapIncrease(const char x, const int y);

        constexpr Vector();
        constexpr Vector(const Vector<T> vector);
        constexpr Vector(const initializer_list<T> initializerList);
        constexpr Vector(const T arr[]);
        constexpr Vector(const size_t capasity)
        constexpr ~Vector();

        constexpr T& operator[] (const size_t index);
        constexpr Vector<T>& operator() (const size_t startIndex, const size_t endIndex);
        constexpr Vector<T>& operator= (const Vector<T>& vector);
        constexpr Vector<T>& operator= (const std::initializer_list<T>& initializerList);
        constexpr Vector<T>& operator= (const T arr[]);

        constexpr bool operator==(const Vector<T>& vector);

        constexpr bool empty();
        constexpr int size();
        constexpr void clear();

        constexpr T& front();
        constexpr T& end();

        constexpr void pushBack(constT val);
        constexpr void popBack();

        constexpr void insert(const size_t index, T val);
        constexpr void insert(const size_t index, vector<T> vector);
        constexpr void insert(const size_t index, initializer_list<T> initializerList);
        constexpr void insert(const size_t index, T arr[])

        constexpr void pop(size_t index);
        constexpr void pop(size_t startIndex, size_t endIndex);

        constexpr Vector<T>& mergeSort();
        constexpr Vector<T>& bubbleSort();

        constexpr size_t binarySerch(T val);
    }; 
}

#include "Vector.tpp"

