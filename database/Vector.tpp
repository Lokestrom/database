#include <initializer_list>
#include <cstdlib>

namespace Database {
    template <typename T>
    constexpr void Vector<T>::changeCapIncrease(const char how, const int val){
        if(how == '+')
            this->capIncrease[0] = 0;
        else if(how == '*')
            this->capIncrease[0] = 1;
        else
            std::exit(1);
        
        this->capIncrease[1] = val;
    }

    template <typename T>
    constexpr Vector<T>::Vector()
    {
        if(this->arr != nullptr)
            delete[] this->arr;
        this->arr = new T[2];
        this->capacity = 2;
    }

    template<typename T>
    constexpr Vector<T>::Vector(const std::initializer_list<T> initializerList) 
    {
        *this = initializerList;
    }

    template<typename T>
    constexpr Vector<T>::Vector(size_t capacity)
        : capacity(capacity)
    {
        if(this->arr != nullptr)
            delete[] this->arr;
        this->arr = new T[capacity];
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
        if (index >= size) {
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
    constexpr Vector<T>& Vector<T>::operator= (const std::initializer_list<T>& x)
    {
        if (capacity < x.size()) {
            if(arr != nullptr)
                delete[] arr;
            capacity = x.size();
            arr = new T[capacity];
        }
        int j = 0;
        for (T i : x) {
            arr[j] = i;
            j++;
        }
        size = x.size();
        return *this;
    }

    template <typename T>
    constexpr Vector<T>& Vector<T>::operator= (const Vector<T>& x)
    {
        if (capacity < x.size) {
            if(arr != nullptr)
                delete[] arr;
            capacity = x.capacity;
            arr = new T[capacity];
        }
        for (int i = 0; i < x.size; i++)
            arr[i] = x.arr[i];
        size = x.size;
        return *this;
    }

    template <typename T>
    constexpr bool Vector<T>::operator==(const Vector<T>& vec1, const Vector<T>& vec2){
        if (vec1.size() != vec2.size())
            return false;

        for (int i = 0; i < size; i++)
            if (vec1[i] != vec2[i])
                return false;
        return true;
    }

    template <typename T>
    constexpr bool Vector<T>::operator!=(const Vector<T>& vec1, const Vector<T>& vec2) {
        return !(vec1 == vec2);
    }

    template<typename T>
    constexpr bool Vector<T>::empty(){
        return size == 0;
    }

    template<typename T>
    constexpr int Vector<T>::size(){
        return size;
    }

    template<typename T>
    constexpr void Vector<T>::clear(){
        size = 0;
    }

    template<typename T>
    constexpr T& Vector<T>::front(){
        return *this[0];
    }

    template<typename T>
    constexpr T& Vector<T>::end(){
        return *this[size-1];
    }

    template <typename T>
    constexpr void Vector<T>::pushBack(const T val)
    {
        if (size == capacity) {
            T* temp;
            if (capIncrease[0] = 0) {
                temp = new T[capacity + capIncrease[1]];
                capacity += capIncrease[1];
            }
            else {
                temp = new T[capacity * capIncrease[1]];
                capacity *= capIncrease[1];
            }

            for (auto i = 0; i < capacity; i++) {
                temp[i] = arr[i];
            }

            if(arr != nullptr)
                delete[] arr;
            arr = temp;
        }
        arr[size] = val;
        size++;
    }

    template<typename T>
    constexpr void Vector<T>::popBack(){
        size--;
    }

    template<typename T>
    constexpr void Vector<T>::insert(const size_t index, const T val){
        T temp[size];
        for(int i = index; i < size; i++)
            temp[i-index] = arr[i];
    
        size = index+1;
        pushBack(val);
        for(T i : temp)
            pushBack(i);
    }

    template<typename T>
    constexpr void Vector<T>::insert(const size_t index, Vector<T> vector){
        for(int i = vector.size(); i > 0 i--)
            insert(index, vector[i]);
    }

    template<typename T>
    constexpr void Vector<T>::insert(const size_t index, std::initializer_list<T> initializerList){
        vector<T> vec = initializerList;
        insert(index, vec);
    }

    template<typename T>
    constexpr void Vector<T>::insert(const size_t index, T arr[]){
        vector<T> vec = arr;
        insert(index, vec);
    }

    template<typename T>
    constexpr void Vector<T>::pop(const size_t index){
        T temp[size];
        for(int i = index+1; i < size; i++)
            temp[i-index] = arr[i];

        size = index;
        for(T i : temp)
            pushBack(i);
    }

    template<typename T>
    constexpr void Vector<T>::pop(size_t startIndex, size_t endIndex){
        T temp[size];
        for(int i = endIndex+1; i < size; i++)
            temp[i-endIndex] = arr[i];

        size = startIndex;
        for(T i : temp)
            pushBack(i);
    }


    template <typename T>
    constexpr Vector<T>& Vector<T>::mergeSort() 
    {
        if (size == 1)
            return *this;

        Vector<T> start;
        start = this->operator()(0, size / 2);
        Vector<T> end;
        end = this->operator()(size / 2, size);
        
        start.mergeSort();
        end.mergeSort();

        *this = {};

        size_t startPos = 0, endPos = 0;
        while (startPos != start.size && endPos == end.size) {
            if (start[startPos] > end[endPos]) {
                pushBack(start[startPos]);
                startPos++;
            }
            else {
                pushBack(end[endPos]);
                endPos++;
            }
        }

        for (;startPos != start.size; startPos++)
            pushBack(start[startPos]);
        for (;endPos != end.size; endPos++)
            pushBack(end[endPos]);

        return *this;
    }

    template<typename T>
    constexpr Vector<T>& Vector<T>::bubbleSort(){
        T temp;
        for (auto i = 0; i < this->size(); i++)
        {
            for (auto j = i + 1; j < this->size(); j++)
            {
                if (*this[i] > *this[j])
                {
                    temp = *this[i];
                    *this[i] = *this[j];
                    *this[j] = temp;
                }
            }
        }
        return *this;
    }

    template<typename T>
    constexpr size_t Vector<T>::binarySerch(T val){
        size_t low = 0;
        size_t high = this->size() - 1;
        size_t mid;

        while (low <= high)
        {
            mid = (low + high) / 2;

            if (*this[mid] == target)
                return mid;
            else if (*this[mid] > target)
                high = mid - 1;
            else
                low = mid + 1;
        }
       
    }
}