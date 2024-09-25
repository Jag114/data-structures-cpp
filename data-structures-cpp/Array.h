#pragma once

#include <initializer_list>
#include <iostream>
#include <algorithm>

/*
TODO:
.insert - add array into array
    Array<int> arr1 = {1,2,5}
    Array<int> arr2 = {3,4}
    arr1.insert(start index, array, nubmer of elems)
    arr1 = {1,2,3,4,5}
.set - set to 0 default, or set value if given
visual representation - opengl?

FIX:
check if sorted in constructor? constructor with sorted var?
delete - edge cases

MODIFY:
Add with no index = push_back
Add with negative index = backwards
add consts and references
growing capacity when adding new elements
*/

template <typename T>
class Array {
private:
    T* m_arrayPointer = nullptr;
    size_t m_size = 0;
    size_t m_capacity = m_size;
    bool m_sorted = false;

    size_t BinarySearch(T target, size_t l, size_t r, size_t m);
public:
    class iterator {
    private:
        T* pointer = nullptr;
    public:
        iterator(T* ptr) {
            pointer = ptr;
        }

        iterator operator+(int offset) {
            return iterator(pointer+offset);
        }

        iterator& operator++() {//pre
            pointer++;
            return *this;
        }

        iterator operator++(int) {//post
            iterator temp = *this;
            pointer++;
            return temp;
        }

        iterator& operator=(const iterator& other) {
            pointer = other.pointer;
            return *this;
        }

        bool operator!=(const iterator& other) {
            return other.pointer != pointer;
        }

        bool operator==(const iterator& other) {
            return other.pointer == pointer;
        }

        T operator*() {
            return *pointer;
        }

    };

    Array();

    Array(size_t size);

    Array(std::initializer_list<T> list);

    Array(const Array& other);

    ~Array();

    Array<T>& operator=(const Array& other);

    Array<T>& operator+(const Array& other);

    T operator[](const size_t index);

    size_t GetLength();

    size_t GetCapacity();

    bool IsSorted();

    void Display();

    void Add(size_t index, T value);
    void Add(T value); //back

    bool Delete(size_t index, size_t amount);

    T Front();

    iterator Begin();

    T Back();

    iterator End();

    size_t Find(T target);

    void Sort(bool (*compare)(T, T));

    void Reserve(size_t size);
};

template <typename T>
size_t Array<T>::BinarySearch(T target, size_t l, size_t r, size_t m) {
    if (l == m || r == m) {
        return m_size;
    }
    
    if (target > m_arrayPointer[m]) {
        l = m;
        m = (l + r) / 2;
        BinarySearch(target, l, r, m);
    }
    else if (target < m_arrayPointer[m]) {
        r = m;
        m = (l + r) / 2;
        BinarySearch(target, l, r, m);
    }
    else {
        return m;
    }
}

template <typename T>
Array<T>::Array() = default;

template <typename T>
Array<T>::Array(size_t size) : m_size(size), m_capacity(size) {
    m_arrayPointer = new T[size];
}

template <typename T>
Array<T>::Array(std::initializer_list<T> list) {
    m_size = list.size();
    m_capacity = m_size;
    m_arrayPointer = new T[m_capacity];

    int i = 0;
    for (const T& elem : list) {
        m_arrayPointer[i] = elem;//ignore buffer overrrun warning
        i++;
    }
}

template <typename T>
Array<T>::Array(const Array& other) {
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    m_arrayPointer = new T[m_capacity];
    
    for (size_t i = 0; i < other.m_size; i++) {
        m_arrayPointer[i] = other.m_arrayPointer[i];
    }
}

template <typename T>
Array<T>::~Array() {
    delete[] m_arrayPointer;
}

template <typename T>
Array<T>& Array<T>::operator=(const Array& other) {
    if (this != &other) {
        delete[] m_arrayPointer;

        m_size = other.m_size;
        m_capacity = other.m_capacity;
        m_arrayPointer = new T[m_capacity];

        for (size_t i = 0; i < other.m_size; i++) {
            m_arrayPointer[i] = other.m_arrayPointer[i];
        }
    }
    return *this;        
}

template <typename T>
Array<T>& Array<T>::operator+(const Array& other) {
    if (m_size + other.m_size > m_capacity) {
        T* newArr = new T[m_size + other.m_size];
        m_capacity = m_size + other.m_size;

        for (size_t i = 0; i < m_size; ++i) {
            newArr[i] = m_arrayPointer[i];
        }
        for(size_t j = 0; j < other.m_size; ++j)
        {
            newArr[j+m_size] = other.m_arrayPointer[j];
        }

        delete[] m_arrayPointer;
        m_size = m_size + other.m_size;
        m_arrayPointer = newArr;
    }
    else {
        for (size_t j = 0; j < other.m_size; ++j)
        {
            m_arrayPointer[j + m_size] = other.m_arrayPointer[j];
        }
        m_size = m_size + other.m_size;
    }
    return *this;
}

template <typename T>
T Array<T>::operator[](const size_t index) {
    if (index >= m_size || index < 0) {
        std::cerr << "Index out of bounds" << std::endl;
        exit(-1);
    }
    return m_arrayPointer[index];
}

template <typename T>
size_t Array<T>::GetLength() {
    return m_size;
}

template <typename T>
size_t Array<T>::GetCapacity() {
    return m_capacity;
}

template <typename T>
bool Array<T>::IsSorted() {
    return m_sorted;
}

template <typename T>
void Array<T>::Display() {
    for (int i = 0; i < m_size; ++i) {
        std::cout << m_arrayPointer[i] << ' ';
    }
    std::cout << std::endl;
}

template <typename T>
void Array<T>::Add(size_t index, T value) {
    m_size++;
    if (m_capacity < m_size) {
        T* newArr = new T[m_size];
        size_t j = 0;

        for (size_t i = 0; i < m_size; i++) {
            if (i != index) {
                newArr[i] = m_arrayPointer[j];
                j++;
            }
        }

        delete[] m_arrayPointer;
        m_arrayPointer = newArr;
        m_capacity++;
    }
    m_arrayPointer[index] = value;
}

template <typename T>
void Array<T>::Add(T value) {
    m_size++;
    if (m_capacity < m_size) {
        T* newArr = new T[m_size];

        newArr[m_size - 1] = value;

        delete[] m_arrayPointer;
        m_arrayPointer = newArr;
        m_capacity++;
    }
}

template <typename T>
bool Array<T>::Delete(size_t index, size_t amount) {
    if (index > m_size - 1 || m_size == 0) return false;

    m_size--;
    T* newArr = new T[m_size];
    size_t j = 0;

    for (size_t i = 0; i < m_size + 1; i++) {
        if (i != index) {
            newArr[j] = m_arrayPointer[i];//buffer overrun?
            j++;
        }
    }

    delete[] m_arrayPointer;
    m_arrayPointer = newArr;

    return true;
}

/*
template <typename T>
 Array<T>::
*/

template <typename T>
T Array<T>::Front() {
    return m_arrayPointer[0];
}

template <typename T>
typename Array<T>::iterator Array<T>::Begin() {
    return iterator(m_arrayPointer);
}

template <typename T>
T Array<T>::Back() {
    return m_arrayPointer[m_size - 1];
}


template <typename T>
typename Array<T>::iterator Array<T>::End() {
    return iterator(m_arrayPointer + m_size);
}


template <typename T>
size_t Array<T>::Find(T target) {
    int result  = m_size;
    if (m_sorted) {
        size_t l, r, m;
        l = 0;
        r = m_size - 1;
        m = (m_size - 1) / 2;
        result = BinarySearch(target, l, r, m);
    }
    else {
        for (size_t i = 0; i < m_size; i++) {
            if (target == m_arrayPointer[i]) {
                result = i;
                break;
            }
        }
    }

    if (result >= m_size) std::cerr << "Target not found" << std::endl;
    return result;
}

template <typename T>
void Array<T>::Sort(bool (*compare)(T,T)) { //Bubble
    /*
    compare(int a, int b){
        return a > b;
    }
    if a > b = true > swap(a,b)
    */  
    std::sort(m_arrayPointer, m_arrayPointer + m_size);

    for (size_t j = 0; j < m_size - 1; j++) {
        if (m_arrayPointer[j] <= m_arrayPointer[j + 1]) {
            m_sorted = true;
        }
        else {
            m_sorted = false;
        }
    }

    if (!m_sorted) {
        Sort(compare);
    }
}

template <typename T>
void Array<T>::Reserve(size_t size) {
    T* newArr = new T[m_size + size];
    m_capacity += size;
    for (size_t i = 0; i < m_size; ++i) {
        newArr[i] = m_arrayPointer[i];
    }
    delete[] m_arrayPointer;
    m_arrayPointer = newArr;
}
