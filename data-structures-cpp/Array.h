#pragma once

#include <initializer_list>
#include <iostream>
#include <algorithm>
#include <cstddef>

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
delete - edge cases

MODIFY:
Add with no index = push_back
Add with negative index = backwards
growing capacity when adding new elements
*/

template <typename T>
class Array {
private:
    T* m_arrayPointer = nullptr;
    size_t m_size = 0;
    size_t m_capacity = m_size;

public:
    class iterator : public std::iterator<std::random_access_iterator_tag, T> {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

    private:
        pointer m_pointer = nullptr;

    public:
        iterator(pointer ptr) : m_pointer(ptr) {}

        iterator operator+(int offset) {
            return iterator(m_pointer+offset);
        }

        iterator& operator++() {//pre
            m_pointer++;
            return *this;
        }

        iterator operator++(int) {//post
            iterator temp = *this;
            m_pointer++;
            return temp;
        }

        iterator& operator--() {
            m_pointer--;
            return *this;
        }

        iterator operator--(int) {
            iterator temp = *this;
            m_pointer--;
            return temp;
        }

        iterator& operator=(const iterator& other) {
            m_pointer = other.m_pointer;
            return *this;
        }
        /*
            it - it = wartosc
            it - wartosc = it
        */
        /*
        _Vb_const_iterator operator-(const difference_type _Off) const noexcept {
            _Vb_const_iterator _Tmp = *this;
            _Tmp -= _Off;
            return _Tmp;
        }
        */
        iterator operator-(std::ptrdiff_t offset) const {
            return iterator(m_pointer - offset);
        }
        /*
        difference_type operator-(const _Vb_const_iterator& _Right) const noexcept {
            return static_cast<difference_type>(_Mybase::_VBITS_DIFF * (this->_Myptr - _Right._Myptr))
                 + static_cast<difference_type>(this->_Myoff) - static_cast<difference_type>(_Right._Myoff);
        }
        */
        std::ptrdiff_t operator-(const iterator& other) const {
            return m_pointer - other.m_pointer;
        }

        bool operator!=(const iterator& other) const {
            return other.m_pointer != m_pointer;
        }

        bool operator==(const iterator& other) const {
            return other.m_pointer == m_pointer;
        }

        bool operator<(const iterator& other) const {
            return other.m_pointer < m_pointer;
        }

        bool operator>(const iterator& other) const {
            return other.m_pointer > m_pointer;
        }

        bool operator<=(const iterator& other) const {
            return other.m_pointer <= m_pointer;
        }

        bool operator>=(const iterator& other) const {
            return other.m_pointer >= m_pointer;
        }

        reference operator*() const {
            return *m_pointer;
        }

        pointer operator->() const { 
            return m_pointer;
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

    void Display();

    void Add(size_t index, T value);
    void Add(T value); //back
    void Add(size_t index, Array<T> array);

    bool Delete(size_t index, size_t amount);

    T Front();

    iterator Begin();

    T Back();

    iterator End();

    size_t Find(T target);

    void Reserve(size_t size);
};

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

        //newArr[m_size - 1] = value;

        delete[] m_arrayPointer;
        m_arrayPointer = newArr;
        m_capacity++;
    }
    m_arrayPointer[m_size - 1] = value;
}

template <typename T>
void Array<T>::Add(size_t index, Array<T> array) {
    m_size += array.m_size;

    T* newArr = new T[m_size];

    for (size_t i = 0; i < index; ++i) {
        newArr[i] = m_arrayPointer[i];
    }

    for (size_t j = index, i = 0; j < array.m_size + index; ++j, ++i) {
        newArr[j] = array[i];
    }

    for (size_t i = array.m_size + index; i < m_size; i++) {
        newArr[i] = m_arrayPointer[i];
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
    //TODO change sort
    std::sort(this->Begin(), this->End(), [](T a, T b) {return a > b; });
    size_t l, r, m;
    l = 0;
    r = m_size - 1;
    m = (m_size - 1) / 2;
    result = BinarySearch(target, l, r, m);
    
    if (result >= m_size) std::cerr << "Target not found" << std::endl;
    return result;
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
