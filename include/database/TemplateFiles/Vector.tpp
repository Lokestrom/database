/*
Author: Loke Strøm
*/
#include <initializer_list>
#include <utility>
#include "Exception.hpp"

namespace Database {

    template <TrivialElement T>
    Vector<T>::Vector() noexcept
    {
        _arr = new T[2];
        _currentCapacity = 2;
        _currentSize = 0;
    }

    template <TrivialElement T>
    Vector<T>::Vector(const Vector<T>& vector) noexcept {
		*this = Vector(vector._currentCapacity);
		*this = vector;
    }
    template <TrivialElement T>
    Vector<T>::Vector(Vector<T>&& vector) noexcept {
        this->_arr = vector._arr;
        this->_currentSize = vector._currentSize;
        this->_currentCapacity = vector._currentCapacity;
        vector._arr = nullptr;
    }

    template <TrivialElement T>
    Vector<T>::Vector(const std::initializer_list<T> initializerList) noexcept
    {
        *this = initializerList;
    }

    template <TrivialElement T>
    Vector<T>::Vector(const std::vector<T>& vector) noexcept {
        reserve(vector.size());
        for (const T& i : vector) {
            pushBack(i);
        }
    }

    template<TrivialElement T>
    Vector<T>::Vector(T&& arr, size_t size) noexcept {
        this->_arr = arr;
        this->_currentSize = size;
        this->_currentCapacity = size;
        arr = nullptr;
    }

    template <TrivialElement T>
    Vector<T>::Vector(const size_t capacity) noexcept
        : _currentCapacity(capacity)
    {
        if(_arr != nullptr)
            delete[] _arr;
        _arr = new T[_currentCapacity];
    }

    template <TrivialElement T>
    Vector<T>::Vector(const size_t count, const T value) noexcept {
        reserve(count);
        for (auto i = 0; i < count; i++)
            pushBack(value);
    }

    template <TrivialElement T>
    Vector<T>::~Vector() noexcept
    {
        if(_arr != nullptr)
            delete[] _arr;
    }

    template <TrivialElement T>
    T& Vector<T>::operator[] (const size_t index) noexcept
    {
        return _arr[index];
    }

    template <TrivialElement T>
    T& Vector<T>::operator[] (const size_t index) const noexcept {
        return _arr[index];
    }

    template <TrivialElement T>
    Vector<T> Vector<T>::operator() (const size_t startIndex, const size_t endIndex) const {
        if (startIndex >= _currentSize)
            throw OutOfRange("startIndex out of range");
        if (endIndex > _currentSize)
            throw OutOfRange("endIndex out of range");
        if(startIndex > endIndex)
            throw OutOfRange("startIndex can't be greater than endIndex");

        Vector<T> x;
        for (auto i = startIndex; i < endIndex; i++)
            x.pushBack(_arr[i]);
        return x;
    }

    template <TrivialElement T>
    Vector<T>& Vector<T>::operator= (const Vector<T>& x) noexcept
    {
        if (_currentCapacity < x._currentSize) {
            if(_arr != nullptr)
                delete[] _arr;
            _currentCapacity = x._currentCapacity;
            _arr = new T[_currentCapacity];
        }
        for (auto i = 0; i < x._currentSize; i++)
            _arr[i] = x._arr[i];
        _currentSize = x._currentSize;
        return *this;
    }

    template<TrivialElement T>
    Vector<T>& Vector<T>::operator= (Vector<T>&& vector) noexcept {
        this->_arr = vector._arr;
        this->_currentSize = vector._currentSize;
        this->_currentCapacity = vector._currentCapacity;
        vector._arr = nullptr;
        vector._currentSize = 0;
        vector._currentCapacity = 0;
        return *this;
    }

    template <TrivialElement T>
    Vector<T>& Vector<T>::operator= (const std::initializer_list<T> initializerList) noexcept
    {
        if (_currentCapacity < initializerList.size()) {
            if (_arr != nullptr)
                delete[] _arr;
            _currentCapacity = initializerList.size();
            _arr = new T[_currentCapacity];
        }
        int j = 0;
        for (auto i : initializerList) {
            _arr[j] = i;
            j++;
        }
        _currentSize = initializerList.size();
        return *this;
    }

    /*template<typename T>
    constexpr Vector<T>& Vector<T>::operator= (const T arr_[]){
        size_t arrSize = 0;
        for (T i : arr_)
            arrSize++;

        if (currentCapacity < arrSize) {
            if (arr != nullptr)
                delete[] arr;
            currentCapacity = arrSize;
            arr = new T[currentCapacity];
        }
        int j = 0;
        for (T i : arr_) {
            arr[j] = i;
            j++;
        }
        currentSize = arrSize;
        return *this;
    }*/

    template <TrivialElement T>
    Vector<T>& Vector<T>::operator+= (const Vector<T>& vector) noexcept {
        this->reserve(this->_currentSize + vector._currentSize);
        for (const T& i : vector)
            this->pushBack(i);
        return *this;
    }

    template <TrivialElement T>
    bool operator==(const Vector<T>& lsh, const Vector<T>& rsh) noexcept {
        if (lsh.size() != rsh.size())
            return false;

        for (auto i = 0; i < lsh.size(); i++)
            if (lsh[i] != rsh[i])
                return false;
        return true;
    }

    template <typename T>
    bool operator!=(const Vector<T>& lsh, const Vector<T>& rsh) noexcept {
        return !(lsh == rsh);
    }

    template <TrivialElement T>
    T& Vector<T>::at(const size_t index) const {
        if (index >= _currentSize)
            throw OutOfRange("Index out of range");
        return _arr[index];
    }

    template<TrivialElement T>
    bool Vector<T>::empty() const noexcept{
        return _currentSize == 0;
    }

    template<TrivialElement T>
    size_t Vector<T>::size() const noexcept{
        return _currentSize;
    }

    template<TrivialElement T>
    void Vector<T>::clear() noexcept{
        _currentSize = 0;
    }

    template<TrivialElement T>
    size_t Vector<T>::capacity() const noexcept{
        return _currentCapacity;
    }

    template<TrivialElement T>
    void Vector<T>::shrinkToFit() noexcept {
        T* temp = new T[_currentSize];
        _currentCapacity = _currentSize;
        for (auto i = 0; i < _currentSize; i++)
            temp[i] = _arr[i];

        if (_arr != nullptr)
            delete[] _arr;
        _arr = temp;
    }

    template<TrivialElement T>
    void Vector<T>::reserve(const size_t newCapacity){
        if (newCapacity == _currentCapacity) {
            return;
        }
        if (newCapacity < _currentCapacity) {
            throw LengthError("newCapacity can't be less than currentCapacity");
        }
        T* temp = new T[newCapacity];
        for(auto i = 0; i < _currentSize; i++)
            temp[i] = _arr[i];

        if (_arr != nullptr)
            delete[] _arr;
        _arr = temp;
       
        _currentCapacity = newCapacity;
    }

    template<TrivialElement T>
    T* Vector<T>::data() noexcept{
        return _arr;
    }

    template<TrivialElement T>
    T* Vector<T>::data() const noexcept{
        return _arr;
    }

    template<TrivialElement T>
    T* Vector<T>::begin() noexcept {
        return &_arr[0];
    }

    template<TrivialElement T>
    T* Vector<T>::end() noexcept{
        return &_arr[_currentSize];
    }

    template<TrivialElement T>
    T* Vector<T>::begin() const noexcept {
        return &_arr[0];
    }

    template<TrivialElement T>
    T* Vector<T>::end() const noexcept {
        return  &_arr[_currentSize];
    }

    template<TrivialElement T>
    void Vector<T>::pushBack(const T& val) noexcept
    {
        if (_currentSize >= _currentCapacity) {
            size_t newCap = _currentCapacity + (_currentCapacity / 2);
            this->reserve(newCap);
        }
        _arr[_currentSize] = val;
        _currentSize++;
    }

    template<TrivialElement T>
    void Vector<T>::popBack(){
        if(_currentSize == 0)
            throw LengthError("Can't popBack on empty Vector");
        _currentSize--;
    }

    template<TrivialElement T>
    void Vector<T>::insert(const size_t index, T val) {
        if (index > _currentSize)
            throw OutOfRange("Index out of range");

        _currentSize++;
        if (_currentSize > _currentCapacity) {
            size_t newCap = _currentSize + (_currentCapacity / 2);
            T* temp = new T[newCap];

            for (auto i = 0; i < _currentSize; i++) {
                temp[i] = _arr[i];
            }

            _currentCapacity = newCap;

            delete[] _arr;
            _arr = temp;
        }
        T lastVal;
        for (auto i = index; i < _currentSize; i++) {
            lastVal = _arr[i];
            _arr[i] = val;
            val = lastVal;
        }
    }

    template<TrivialElement T>
    void Vector<T>::insert(const size_t index, const Vector<T>& vector) {
        for (auto it = vector.end() - 1; it != vector.begin() - 1; it--)
            insert(index, *it);
    }


    template<TrivialElement T>
    void Vector<T>::insert(const size_t index, const std::initializer_list<T> initializerList) {
        Vector<T> vec = initializerList;
        insert(index, vec);
    }

    /*template<typename T>
    constexpr void Vector<T>::insert(const size_t index, const T arr[]){
        Vector<T> vec = arr;
        insert(index, vec);
    }*/

    template<TrivialElement T>
    void Vector<T>::pop(const size_t index){
        if(index >= _currentSize)
            throw OutOfRange("Index out of range");
        _currentSize--;
        for (auto i = index; i < _currentSize; i++)
            _arr[i] = _arr[i + 1];
    }

    template<TrivialElement T>
    void Vector<T>::pop(const size_t startIndex, const size_t endIndex){
        if(startIndex >= _currentSize)
            throw OutOfRange("startIndex out of range");
        if(endIndex > _currentSize)
            throw OutOfRange("endIndex out of range");
        if(startIndex > endIndex)
            throw OutOfRange("startIndex can't be greater than endIndex");
        
        size_t diff = endIndex - startIndex;
        _currentSize -= diff;
        for (auto i = startIndex; i < _currentSize; i++)
            _arr[i] = _arr[i + diff];
    }


    template<TrivialElement T>
    Vector<T>& Vector<T>::mergeSort() noexcept
    {
        if (_currentSize == 1)
            return *this;

        Vector<T> start;
        start = this->operator()(0, _currentSize / 2);
        Vector<T> end;
        end = this->operator()(_currentSize / 2, _currentSize);
        
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

    template<TrivialElement T>
    Vector<T>& Vector<T>::bubbleSort() noexcept{
        T temp;
        for (auto i = 0; i < _currentSize; i++)
        {
            for (auto j = 0; j < _currentSize - i - 1; j++)
            {
                if (_arr[j] > _arr[j + 1])
                {
                    temp = _arr[j + 1];
                    _arr[j + 1] = _arr[j];
                    _arr[j] = temp;
                }
            }
        }
        return *this;
    }

    template<TrivialElement T>
    long long Vector<T>::binarySearch(const T target) const noexcept {
        long long low = 0;
        long long high = _currentSize - 1;
        long long mid;

        while (low <= high)
        {
            mid = (low + high) / 2;

            if (_arr[mid] == target)
                return mid;
            else if (_arr[mid] > target)
                high = mid - 1;
            else
                low = mid + 1;
        }
        return -1;
    }

    template<TrivialElement T>
    long long Vector<T>::linearSearch(const T target) const noexcept {
        for (auto i = 0; i < _currentSize; i++)
            if (_arr[i] == target)
                return i;
        return -1;
    }

    template<TrivialElement T>
    long long Vector<T>::linearSearchR(const T target) const noexcept {
        for (long long i = _currentSize-1; i > -1; i--)
            if (_arr[i] == target)
                return i;
        return -1;
    }
}