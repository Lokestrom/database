#include <initializer_list>
#include <cstdlib>

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
        cap = 2;
    }

    template<typename T>
    constexpr Vector<T>::Vector(Vector<T>& x){
        *this = x; 
    }

    template<typename T>
    constexpr Vector<T>::Vector(initializer_list<T>& x){
        *this = x;
    }

    template<typename T>
    constexpr Vector<T>::Vector(size_t capasity){
        if(arr != nullptr)
            delete[] arr;
        arr = new T[capasity]
        cap = capasity
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
        if (index >= cur) {
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
        if (cap < x.size()) {
            if(arr != nullptr)
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
    constexpr Vector<T>& Vector<T>::operator= (const Vector<T>& x)
    {
        if (cap < x.cur) {
            if(arr != nullptr)
                delete[] arr;
            cap = x.cap;
            arr = new T[cap];
        }
        for (int i = 0; i < x.cur; i++)
            arr[i] = x.arr[i];
        cur = x.cur;
        return *this;
    }

    constexpr bool operator==(const Vector<T>& vector){
        bool x;
        cur == vector.cur ? x = true : return x;
        for(int i = 0; i < cur; i++)
    }

    template<typename T>
    constexpr bool Vector<T>::empty(){
        return cur == 0;
    }

    template<typename T>
    constexpr int Vector<T>::size(){
        return cur;
    }

    template<typename T>
    constexpr void Vector<T>::clear(){
        cur = 0;
    }

    template<typename T>
    constexpr T& Vector<T>::front(){
        return *this[0];
    }

    template<typename T>
    constexpr T& Vector<T>::end(){
        return *this[cur-1];
    }

    template <typename T>
    constexpr void Vector<T>::pushBack(const T val)
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

            if(arr != nullptr)
                delete[] arr;
            arr = temp;
        }
        arr[cur] = val;
        cur++;
    }

    template<typename T>
    constexpr void Vector<T>::popBack(){
        cur--;
    }

    template<typename T>
    constexpr void Vector<T>::insert(const size_t index, const T val){
        T temp[cur];
        for(int i = index; i < cur; i++)
            temp[i-index] = arr[i];
    
        cur = index+1;
        pushBack(val);
        for(T i : temp)
            pushBack(i);
    }

    template<typename T>
    constexpr void Vector<T>::insert(const size_t index, vector<T> vector){
        for(int i = vector.size(); i > 0 i--)
            insert(index, vector[i]);
    }

    template<typename T>
    constexpr void Vector<T>::insert(const size_t index, initializer_list<T> initializerList){
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
        T temp[cur];
        for(int i = index+1; i < cur; i++)
            temp[i-index] = arr[i];

        cur = index;
        for(T i : temp)
            pushBack(i);
    }

    template<typename T>
    constexpr void Vector<T>::pop(size_t startIndex, size_t endIndex){
        T temp[cur];
        for(int i = endIndex+1; i < cur; i++)
            temp[i-endIndex] = arr[i];

        cur = startIndex;
        for(T i : temp)
            pushBack(i);
    }


    template <typename T>
    constexpr Vector<T>& Vector<T>::mergeSort() 
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

    template<typename T>
    constexpr vector<T>& Vector<T>::bubbleSort(){
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