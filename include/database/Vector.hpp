#pragma once

#include <concepts>
#include <vector>

namespace Database{
    template <typename T>
    concept TrivialElement =
        std::is_trivially_destructible_v<T>;
    template <TrivialElement T>
    class Vector
    {
    private:
        T* _arr = nullptr;
        size_t _currentSize = 0, _currentCapacity = 0;

    public:
        Vector() noexcept;
        Vector(const Vector<T>& vector) noexcept;
        Vector(Vector<T>&& vector) noexcept;
        Vector(const std::initializer_list<T> initializerList) noexcept;
        Vector(const std::vector<T>& vector) noexcept;
        Vector(T&& arr, size_t size) noexcept;
        Vector(const size_t capacity) noexcept;
        Vector(const size_t count, const T value) noexcept;
        ~Vector() noexcept;

        T& operator[] (const size_t index) noexcept;
        T& operator[] (const size_t index) const noexcept;
        Vector<T> operator() (const size_t startIndex, const size_t endIndex) const;

        Vector<T>& operator= (const Vector<T>& vector) noexcept;
        Vector<T>& operator= (Vector<T>&& vector) noexcept;
        Vector<T>& operator= (const std::initializer_list<T> initializerList) noexcept;
        //constexpr Vector<T>& operator= (const T arr[]);
                         
        Vector<T>& operator+= (const Vector<T>& vector) noexcept;

        T& at(const size_t index) const;
        bool empty() const noexcept;
        void clear() noexcept;
        size_t size() const noexcept;
        size_t capacity() const noexcept;
        void reserve(const size_t newCapacity);
        T* data() noexcept;
        T* data() const noexcept;
        void shrinkToFit() noexcept;

        T* begin() noexcept;
        T* end() noexcept;

        T* begin() const noexcept;
        T* end() const noexcept;

        void pushBack(const T& val) noexcept;
        void popBack();

        void insert(const size_t index, T val);
        void insert(const size_t index, const Vector<T>& vector);
        void insert(const size_t index, const std::initializer_list<T> initializerList);
        //constexpr void insert(const size_t index, const T arr[]);

        void pop(const size_t index);
        void pop(const size_t startIndex, const size_t endIndex);

        Vector<T>& mergeSort() noexcept;
        Vector<T>& bubbleSort() noexcept;

        long long binarySearch(const T target) const noexcept;
        long long linearSearch(const T target) const noexcept;
        long long linearSearchR(const T target) const noexcept;
    };

    template <TrivialElement T>
    bool operator== (const Vector<T>& lhs, const Vector<T>& rhs) noexcept;
    template <TrivialElement T>
    bool operator!= (const Vector<T>& lhs, const Vector<T>& rhs) noexcept;
}

#include "TemplateFiles/Vector.tpp"

