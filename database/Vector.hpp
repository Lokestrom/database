#pragma once

#include <initializer_list>

namespace Database{
    template <typename T>
    class Vector
    {
    private:
        T* arr = nullptr;
        size_t currentSize = 0, capacity = 0;
        int capIncrease[2] = { 1, 2 };

    public:

        constexpr void changeCapIncrease(const char x, const int y);

        constexpr Vector();
        constexpr Vector(const std::initializer_list<T> initializerList);
        constexpr Vector(const T arr[]);
        constexpr Vector(const size_t capasity);
        constexpr ~Vector();

        constexpr T& operator[] (const size_t index);
        constexpr Vector<T> operator() (const size_t startIndex, const size_t endIndex);
        constexpr Vector<T>& operator= (const Vector<T>& vector);
        constexpr Vector<T>& operator= (const std::initializer_list<T>& initializerList);
        constexpr Vector<T>& operator= (const T arr[]);

        constexpr bool operator==(const Vector<T>& vec);
        constexpr bool operator!=(const Vector<T>& vec);

        constexpr bool empty();
        constexpr int size();
        constexpr void clear();

        constexpr T& front();
        constexpr T& end();

        constexpr void pushBack(const T val);
        constexpr void popBack();

        constexpr void insert(const size_t index, T val);
        constexpr void insert(const size_t index, Vector<T> vector);
        constexpr void insert(const size_t index, std::initializer_list<T> initializerList);
        constexpr void insert(const size_t index, T arr[]);

        constexpr void pop(size_t index);
        constexpr void pop(size_t startIndex, size_t endIndex);

        constexpr Vector<T>& mergeSort();
        constexpr Vector<T>& bubbleSort();

        constexpr size_t binarySerch(T val);
    }; 
}

#include "Vector.tpp"

