#include <initializer_list>
#include <cstdlib>
#include <iostream>

namespace Database {
    template <typename T>
    constexpr void Vector<T>::changeCapIncrease(const char how, const int val){
        if(how == '+')
            capIncrease[0] = 0;
        else if(how == '*')
            capIncrease[0] = 1;
        else
            std::exit(1);
        
        capIncrease[1] = val;
    }

    template <typename T>
    constexpr Vector<T>::Vector()
    {
        if(arr != nullptr)
            delete[] arr;
        arr = new T[2];
        capacity = 2;
    }

    template <typename T>
    constexpr Vector<T>::Vector(const Vector<T>& vector){
        *this = vector;
    }

    template<typename T>
    constexpr Vector<T>::Vector(const std::initializer_list<T> initializerList) 
    {
        this = initializerList;
    }

    template<typename T>
    constexpr Vector<T>::Vector(const T arr[]){
        this = arr;
    }

    template<typename T>
    constexpr Vector<T>::Vector(size_t capacity_)
        : capacity(capacity_)
    {
        if(arr != nullptr)
            delete[] arr;
        arr = new T[capacity];
    }

    template <typename T>
    constexpr Vector<T>::~Vector()
    {
        if(arr != nullptr)
            delete[] arr;
    }

    template <typename T>
    constexpr T& Vector<T>::operator[] (const size_t index)
    {
        if (index >= currentSize) {
            std::cout << "index out of range\n";
            std::exit(1);
        }
        return arr[index];
    }

    template <typename T>
    constexpr Vector<T> Vector<T>::operator() (const size_t startIndex, const size_t endIndex) {
        Vector<T> x;
        for (auto i = startIndex; i < endIndex; i++)
            x.pushBack(arr[i]);
        return x;
    }

    template <typename T>
    constexpr Vector<T>& Vector<T>::operator= (const Vector<T>& x)
    {
        if (capacity < x.currentSize) {
            if(arr != nullptr)
                delete[] arr;
            capacity = x.capacity;
            arr = new T[capacity];
        }
        for (int i = 0; i < x.currentSize; i++)
            arr[i] = x.arr[i];
        currentSize = x.currentSize;
        return *this;
    }

    template <typename T>
    constexpr Vector<T>& Vector<T>::operator= (const std::initializer_list<T>& initializerList)
    {
        if (capacity < initializerList.size()) {
            if (arr != nullptr)
                delete[] arr;
            capacity = initializerList.size();
            arr = new T[capacity];
        }
        int j = 0;
        for (T i : initializerList) {
            arr[j] = i;
            j++;
        }
        currentSize = initializerList.size();
        return *this;
    }

    template<typename T>
    constexpr Vector<T>& Vector<T>::operator= (const T arr_[]){
        size_t arrSize = 0;
        for (T i : arr_)
            arrSize++;

        if (capacity < arrSize) {
            if (arr != nullptr)
                delete[] arr;
            capacity = arrSize;
            arr = new T[capacity];
        }
        int j = 0;
        for (T i : arr_) {
            arr[j] = i;
            j++;
        }
        currentSize = arrSize;
        return *this;
    }

    template <typename T>
    constexpr bool Vector<T>::operator==(const Vector<T>& vec){
        if (currentSize != vec.size())
            return false;

        for (int i = 0; i < currentSize; i++)
            if (*this[i] != vec[i])
                return false;
        return true;
    }

    template <typename T>
    constexpr bool Vector<T>::operator!=(const Vector<T>& vec) {
        return !(this == vec);
    }

    template<typename T>
    constexpr bool Vector<T>::empty(){
        return currentSize == 0;
    }

    template<typename T>
    constexpr size_t Vector<T>::size(){
        return currentSize;
    }

    template<typename T>
    constexpr void Vector<T>::clear(){
        currentSize = 0;
    }

    template<typename T>
    constexpr void Vector<T>::setCapacity(size_t newCapacity){
        capacity = newCapacity;
        T temp[size];
        for(auto i = 0; i < size; i++)
            temp[i] = arr[i];

        arr = new T[capacity];
        for(auto i = 0; i < size; i++)
            arr[i] = temp[i];
        
    }

    template<typename T>
    constexpr T* Vector<T>::begin(){
        return *this[0];
    }

    template<typename T>
    constexpr T* Vector<T>::end(){
        return *this[currentSize - 1];
    }

    template <typename T>
    constexpr void Vector<T>::pushBack(const T val)
    {
        if (currentSize == capacity) {
            T* temp = (capIncrease[0] == 0) 
                ? new T[capacity + capIncrease[1]]
                : new T[capacity * capIncrease[1]];

            for (auto i = 0; i < capacity; i++) {
                temp[i] = arr[i];
            }

            capacity = (capIncrease[0] == 0)
                ? capacity + capIncrease[1]
                : capacity * capIncrease[1];

            if(arr != nullptr)
                delete[] arr;
            arr = temp;
        }
        arr[currentSize] = val;
        currentSize++;
    }

    template<typename T>
    constexpr void Vector<T>::popBack(){
        currentSize--;
    }

    template<typename T>
    constexpr void Vector<T>::insert(const size_t index, const T val){
        T temp[currentSize];
        for(int i = index; i < currentSize; i++)
            temp[i-index] = arr[i];
    
        currentSize = index+1;
        pushBack(val);
        for(T i : temp)
            pushBack(i);
    }

    template<typename T>
    constexpr void Vector<T>::insert(const size_t index, Vector<T> vector){
        for(int i = vector.size(); i > 0; i--)
            insert(index, vector[i]);
    }

    template<typename T>
    constexpr void Vector<T>::insert(const size_t index, std::initializer_list<T> initializerList){
        Vector<T> vec = initializerList;
        insert(index, vec);
    }

    template<typename T>
    constexpr void Vector<T>::insert(const size_t index, T arr[]){
        Vector<T> vec = arr;
        insert(index, vec);
    }

    template<typename T>
    constexpr void Vector<T>::pop(const size_t index){
        auto s = currentSize - index - 1;
        T* temp = new T[s];
        for(auto i = index + 1; i < currentSize; i++)
            temp[i - 1 - index] = arr[i];

        currentSize = index;
        for(auto i = 0; i < s; i++)
            pushBack(temp[i]);
    }

    template<typename T>
    constexpr void Vector<T>::pop(size_t startIndex, size_t endIndex){
        auto s = currentSize - endIndex;
        T* temp = new T[s];
        for(auto i = endIndex; i < currentSize; i++)
            temp[i - endIndex] = arr[i];

        currentSize = startIndex;
        for(auto i = 0; i < s; i++)
            pushBack(temp[i]);
    }


    template <typename T>
    constexpr Vector<T>& Vector<T>::mergeSort() 
    {
        if (currentSize == 1)
            return *this;

        Vector<T> start;
        start = this->operator()(0, currentSize / 2);
        Vector<T> end;
        end = this->operator()(currentSize / 2, currentSize);
        
        start.mergeSort();
        end.mergeSort();

        clear();

        size_t startPos = 0, endPos = 0;
        while (startPos != start.size() && endPos != end.size()) {
            if (start[startPos] < end[endPos]) {
                pushBack(start[startPos]);
                startPos++;
            }
            else {
                pushBack(end[endPos]);
                endPos++;
            }
        }

        for (;startPos != start.size(); startPos++)
            pushBack(start[startPos]);
        for (;endPos != end.size(); endPos++)
            pushBack(end[endPos]);

        return *this;
    }

    template<typename T>
    constexpr Vector<T>& Vector<T>::bubbleSort(){
        T temp;
        for (auto i = 0; i < currentSize; i++)
        {
            for (auto j = i + 1; j < currentSize; j++)
            {
                if (arr[i] > arr[j])
                {
                    temp =  (arr[i]);
                    arr[i] = arr[j];
                    arr[j] = temp;
                }
            }
        }
        return *this;
    }

    template<typename T>
    constexpr size_t Vector<T>::binarySerch(T target){
        long long int low = 0;
        long long int high = currentSize - 1;
        size_t mid;

        while (low <= high)
        {
            mid = (low + high) / 2;

            if (arr[mid] == target)
                return mid;
            else if (arr[mid] > target)
                high = mid - 1;
            else
                low = mid + 1;
        }
        return -1;
    }
}