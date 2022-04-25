#include <initializer_list>
#include <cstdlib>

namespace Database {
    template <typename T>
    Vector<T>::Vector()
    {
        arr = new T[2];
        cap = 1;
        cur = 0;
    }

    template <typename T>
    Vector<T>::~Vector()
    {
        delete[] arr;
    }

    template <typename T>
    T& Vector<T>::operator[] (const size_t index)
    {
        if (index >= cur) {
            std::exit(1);
        }
        return arr[index];
    }

    template <typename T>
    Vector<T> Vector<T>::operator() (const size_t startIndex, const size_t endIndex) {
        Vector<T> x;
        for (auto i = startIndex; i < endIndex; i++)
            x.pushBack(arr[i]);
        return x;
    }

    template <typename T>
    Vector<T>& Vector<T>::operator= (const std::initializer_list<T>& x)
    {
        if (cap < x.size()) {
            delete[] arr;
            cap = x.size();
            arr = new T[cap];
        }
        int j = 0;
        for (T i : x) {
            arr[j] = i;
            j++;
        }
        cur = x.size();
        return *this;
    }

    template <typename T>
    Vector<T>& Vector<T>::operator= (const Vector<T>& x)
    {
        if (cap < x.cur) {
            delete[] arr;
            cap = x.cap;
            arr = new T[cap];
        }
        for (int i = 0; i < x.cur; i++)
            arr[i] = x.arr[i];
        cur = x.cur;
        return *this;
    }

    template <typename T>
    void Vector<T>::pushBack(const T val)
    {
        if (cur == cap) {
            T* temp;
            if (capIncrease[0] = 0) {
                temp = new T[cap + capIncrease[1]];
                cap += capIncrease[1];
            }
            else {
                temp = new T[cap * capIncrease[1]];
                cap *= capIncrease[1];
            }

            for (auto i = 0; i < cap; i++) {
                temp[i] = arr[i];
            }

            delete[] arr;
            arr = temp;
        }
        arr[cur] = val;
        cur++;
    }

    template <typename T>
    Vector<T> Vector<T>::mergeSort() 
    {
        if (cur == 1)
            return *this;

        Vector<T> start;
        start = this->operator()(0, cur / 2);
        Vector<T> end;
        end = this->operator()(cur / 2, cur);
        
        start.mergeSort();
        end.mergeSort();

        *this = {};

        size_t startPos = 0, endPos = 0;
        while (startPos != start.cur && endPos == end.cur) {
            if (start[startPos] > end[endPos]) {
                pushBack(start[startPos]);
                startPos++;
            }
            else {
                pushBack(end[endPos]);
                endPos++;
            }
        }

        for (;startPos != start.cur; startPos++)
            pushBack(start[startPos]);
        for (;endPos != end.cur; endPos++)
            pushBack(end[endPos]);

        return *this;
    }
}