#pragma once

#include <initializer_list>
#include <string>
#include <vector>

namespace Database{

    template <class T>
    constexpr std::string typeOf(T x);
    template <class T>
    constexpr std::string typeOf();

    template <typename T>
    class Vector
    {
    private:
        T* arr = nullptr;
        size_t currentSize = 0, currentCapacity = 0;
        size_t capIncrease[2] = { 1, 2 };

        constexpr std::string errorMsg(const std::string ErrorMsg, const std::string fungtion, const Vector<std::string> fungtionInput, const Vector<std::string> fungtionInputType);
        constexpr std::string errorMsg(const std::string ErrorMsg, const std::string fungtion);
        constexpr std::string constructStringOfVector(const Vector<T> vec);

    public:

        constexpr void changeCapIncrease(const char x, const size_t y);

        constexpr Vector();
        constexpr Vector(const Vector<T>& vector);
        constexpr Vector(const std::initializer_list<T> initializerList);
        constexpr Vector(const std::vector<T>& vector);
        //constexpr Vector(const T arr[]);
        constexpr Vector(const size_t capacity);
        constexpr Vector(const size_t amount, const T x);
        ~Vector();

        constexpr T& operator[] (const size_t index) noexcept;
        constexpr T& operator[] (const size_t index) const noexcept;
        constexpr Vector<T> operator() (const size_t startIndex, const size_t endIndex);

        constexpr Vector<T>& operator= (const Vector<T>& vector) noexcept;
        constexpr Vector<T>& operator= (const std::initializer_list<T>& initializerList) noexcept;
        //constexpr Vector<T>& operator= (const T arr[]);

        constexpr bool operator== (const Vector<T>& vec) noexcept;
        constexpr bool operator== (const std::initializer_list<T>& initializerList) noexcept;
        //constexpr bool operator== (const T arr[]);
        constexpr bool operator!= (const Vector<T>& vec) noexcept;
        constexpr bool operator!= (const std::initializer_list<T>& initializerList) noexcept;
        //constexpr bool operator!= (const T arr[]);

        constexpr T& at(const size_t index) const;
        constexpr bool empty() const noexcept;
        constexpr void clear() noexcept;
        constexpr size_t size() const noexcept;
        constexpr size_t capacity() const noexcept;
        constexpr void reserve(const size_t newCapacity);
        constexpr T* data();
        constexpr T* data() const;
        constexpr void shrinkToFit() noexcept;

        constexpr T* begin() noexcept;
        constexpr T* end() noexcept;

        constexpr T* begin() const noexcept;
        constexpr T* end() const noexcept;

        constexpr void pushBack(const T val) noexcept;
        constexpr void popBack();

        constexpr void insert(const size_t index, const T val);
        constexpr void insert(const size_t index, const Vector<T>& vector);
        constexpr void insert(const size_t index, const std::initializer_list<T> initializerList);
        //constexpr void insert(const size_t index, const T arr[]);

        constexpr void pop(const size_t index);
        constexpr void pop(const size_t startIndex, const size_t endIndex);

        constexpr Vector<T>& mergeSort() noexcept;
        constexpr Vector<T>& bubbleSort() noexcept;
        constexpr Vector<T>& mergeSort() const noexcept;
        constexpr Vector<T>& bubbleSort() const noexcept;

        constexpr long long binarySerch(const T val) noexcept;
        constexpr long long linearSearch(const T val) noexcept;
        constexpr long long binarySerch(const T val) const noexcept;
        constexpr long long linearSearch(const T val) const noexcept;

        //for debuging
        constexpr void printVectorData() noexcept;
    };
}

#include "Vector.tpp"

