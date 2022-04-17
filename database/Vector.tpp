#include "Vector.hpp"

#include <cstdlib>

namespace Database {
    template <typename T>
    Vector<T>::Vector()
    {
        arr = new T[1];
        cap = 1;
        cur = 0;
    }

    template <typename T>
    Vector<T>::~Vector()
    {
        delete[] arr;
    }

    template <typename T>
    T Vector<T>::operator[](int i) 
    {
        if (i >= cur) {
            std::exit(1);
            return arr[0];
        }
        return arr[i];
    }

    template <typename T>
    void Vector<T>::operator = (const Vector<T> x)
    {
        int size = 0;
        for (T i : x) {
            size++;
        }

        cap = size;
        delete[] arr;
        arr = new T[cap];
        for (T i : x) {
            arr.pushBack(i);
        }
    }

    template <typename T>
    void Vector<T>::pushBack(T val)
    {
        if (cur == cap) {
            T* temp;
            if (capIncrease[0] = 0)
                temp = new T[cap + capIncrease];
            else
                temp = new T[cap * capIncrease];

            for (auto i = 0; i < cap; i++) {
                temp[i] = arr[i];
            }

            delete[] arr;
            cap *= 2;
            arr = temp;
        }
        arr[cur] = val;
        cur++;
    }
}