//
// Created by Ismail Magdy on 06/12/2022.
//

#ifndef ASS_3_AIVECTOR_H
#define ASS_3_AIVECTOR_H
#include <iostream>
//---------------------------------------Headers-------------------------------------------------------------------
using namespace std;
template <typename T>
using iterator = T *;

template <typename T>
class AIVector
{
    template <typename type>
    friend std::ostream &operator<<(std::ostream &out, ::AIVector<type>);

public:
    // Constructors
    AIVector(int size = 0);
    AIVector(T *, int n);
    AIVector(const AIVector<T> &other);
    AIVector(AIVector<T> &&other);
    ~AIVector();

    // Assignment
    AIVector<T> &operator=(const AIVector<T> &other);
    AIVector<T> operator=(AIVector<T> &&other);

    // Indexing
    T &operator[](int) const;
    T &operator[](int);

    // getters
    int size() const;
    int capacity() const;
    bool isEmpty() const;

    // reSizing
    void resize(int size);
    void clear();

    // adding , removing elements
    int push_back(const T &element);
    T pop_back();

    // Comparison
    bool operator==(const AIVector<T> &other) const;
    bool operator>(const AIVector<T> &other) const;
    bool operator<(const AIVector<T> &other) const;

    // iterators
    void insert(iterator<T>, T);
    void erase(iterator<T> it);
    void erase(iterator<T> it1, iterator<T> it2);
    iterator<T> begin() const;
    iterator<T> end() const;

private:
    T *arr;
    int arrayCapacity;
    int arraySize;
};
//------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------------IMPELEMENTAION--------------------------------------------------

//----------------------------------------------------Default Constructor------------------------------------------------------
/**
 * @brief default construtor that takes size and allocate a dynamic array of new size
 *        set size to the given size
 * @tparam
 * @param size size required to allocate dynamic array
 */
template <typename T>
AIVector<T>::AIVector(int size)
{
    this->arraySize = size;
    this->arrayCapacity = this->size();
    this->arr = new T[this->size()];
}

//----------------------------------------------------Copy Constructor------------------------------------------------------
/**
 * @brief perform deep copy to avoid dangling pointer and MemoryLeaks
 *
 * @tparam T
 * @param other
 */
template <typename T>
AIVector<T>::AIVector(const AIVector<T> &other)
{
    this->arraySize = other.size();
    this->arrayCapacity = this->size();
    this->arr = new T[this->size()];

    for (int i = 0; i < this->size(); ++i)
    {
        this->arr[i] = other.arr[i];
    }
}

//----------------------------------------------------Copy from Array--------------------------------------------------------

/**
 * @brief array takes copy from the other array
 *
 * @tparam T
 * @param other -> other array to copy from
 * @param n -> size of the elements to copy
 */
template <typename T>
AIVector<T>::AIVector(T *other, int n)
{
    this->arraySize = n;
    this->arrayCapacity = this->size();
    this->arr = new T[this->size()];
    for (int i = 0; i < n; ++i)
    {
        this->arr[i] = other[i];
    }
}

//----------------------------------------------------Move Constructor--------------------------------------------------------
/**
 * @brief Move constuctor to avoid uncessary copies
 *
 * @tparam T
 * @param other
 */
template <typename T>
AIVector<T>::AIVector(AIVector<T> &&other)
{
    this->arr = other.arr;
    this->arraySize = other.size();
    this->arrayCapacity = this->size();

    other.arr = NULL;
    other.arraySize = 0;
    other.arrayCapacity = 0;
}

//----------------------------------------------------Copy Assignment--------------------------------------------------------
/**
 * @brief copy  data
 *
 * @tparam T
 * @param other
 * @return AIVector<T>&
 */
template <typename T>
AIVector<T> &AIVector<T>::operator=(const AIVector<T> &other)
{
    if (&other == this)
        return *this;
    delete[] arr;

    this->arraySize = other.size();
    this->arrayCapacity = this->size();
    this->arr = new T[this->size()];

    for (int i = 0; i < this->size(); ++i)
    {
        this->arr[i] = other.arr[i];
    }
    return *this;
}

// Move assignment
/**
 * @brief the array before the = sign get all the properties from the other array after the = sign
 *
 * @tparam T
 * @param other
 * @return AIVector<T>
 */
template <typename T>
AIVector<T> AIVector<T>::operator=(AIVector<T> &&other)
{
    this->arr = other.arr;
    this->arraySize = other.size();
    this->arrayCapacity = this->size();

    other.arr = NULL;
    other.arraySize = 0;
    other.arrayCapacity = 0;

    return *this;
}

// Destructor
template <typename T>
AIVector<T>::~AIVector()
{
    delete[] this->arr;
}

// Indexing

template <typename T>
T &AIVector<T>::operator[](int position)
{
    if (position < 0 || position >= capacity())
        throw("Out of Bounds\n");
    return arr[position];
}

template <typename T>
T &AIVector<T>::operator[](int position) const
{
    if (position < 0 || position >= capacity())
        throw("Out of Bounds\n");
    return arr[position];
}

// removing  elements
template <typename T>
T AIVector<T>::pop_back()
{
    if (this->isEmpty())
        throw("Already Empty vector\n");
    arraySize--;
    return this->arr[size() + 1];
}

// adding elements
template <typename T>
int AIVector<T>::push_back(const T &element)
{
    if (size() >= capacity())
    {
        int newCapacity = this->size() * 2;
        T *doubleSizeArray = new T[newCapacity];
        for (int i = 0; i < this->size(); ++i)
        {
            doubleSizeArray[i] = this->arr[i];
        }
        doubleSizeArray[this->size()] = element;
        delete[] this->arr;
        arr = doubleSizeArray;
        this->arraySize++;
        this->arrayCapacity = newCapacity;
        doubleSizeArray = NULL;
    }
    else
    {
        this->arr[arraySize] = element;
        this->arraySize++;
    }
    return size();
}

// Comparison
/**
 * @brief < operator
 *
 * @tparam T
 * @param other
 * @return true
 * @return false
 */
template <typename T>
bool AIVector<T>::operator<(const AIVector<T> &other) const
{
    int size = min(this->size(), other.size());
    for (int i = 0; i < size; ++i)
    {
        if ((*this)[i] < other[i])
            return true;
        if ((*this)[i] > other[i])
            return false;
    }
    return false;
}
/**
 * @brief > operator
 *
 * @tparam T
 * @param other
 * @return true
 * @return false
 */
template <typename T>
bool AIVector<T>::operator>(const AIVector<T> &other) const
{
    int size = min(this->size(), other.size());
    for (int i = 0; i < size; ++i)
    {
        if ((*this)[i] > other[i])
            return true;
        if ((*this)[i] < other[i])
            return false;
    }
    return false;
}
/**
 * @brief == operator
 *
 * @tparam T
 * @param other
 * @return true
 * @return false
 */
template <typename T>
bool AIVector<T>::operator==(const AIVector<T> &other) const
{
    if (this->size() != other.size())
        return false;
    int size = this->size();
    for (int i = 0; i < size; ++i)
    {
        if ((*this)[i] != other[i])
            return false;
    }
    return true;
}

// getters
/**
 * @brief return number of occupied elements
 *
 * @tparam T
 * @return size of array
 */
template <typename T>
int AIVector<T>::size() const
{
    return this->arraySize;
}

/**
 * @brief return number of Reserved Element in the memory
 *
 * @tparam T
 * @return the capacity of the array
 */
template <typename T>
int AIVector<T>::capacity() const
{
    return this->arrayCapacity;
}

/**
 * @brief check if no elements occupy the memory
 *
 * @tparam T
 * @return true
 * @return false
 */
template <typename T>
bool AIVector<T>::isEmpty() const
{
    return this->size() == 0;
}

// reSizing
template <typename T>
void AIVector<T>::resize(int newSize)
{
    if (newSize <= this->size())
    {
        this->arraySize = newSize;
    }
    else
    {
        T *newArray = new T[newSize];
        for (int i = 0; i < size(); ++i)
        {
            newArray[i] = this->arr[i];
        }
        delete[] arr;
        this->arr = newArray;
        this->arraySize = newSize;
        this->arrayCapacity = size();
        newArray = NULL;
    }
}

// setting all elements to default values
template <typename T>
void AIVector<T>::clear()
{
    for (int i = 0; i < this->size(); ++i)
    {
        this->arr[i] = T();
    }
    this->arraySize = 0;
}

// printing
template <typename T>
std::ostream &operator<<(std::ostream &out, AIVector<T> vector)
{
    int size = vector.size();
    for (int i = 0; i < size; ++i)
    {
        out << vector.arr[i] << " ";
    }
    return out;
}

template <typename T>
using Iterator = T *;
template <typename T>
void AIVector<T>::erase(Iterator<T> it)
{
    if (it < begin() || it >= end())
    {
        throw("Invalid iterator\n");
    }
    int idx = it - begin();

    for (int i = idx + 1; i < this->size(); ++i)
    {
        this->arr[i - 1] = this->arr[i];
    }
    this->arraySize--;
}

template <typename T>
using Iterator = T *;
template <typename T>
void AIVector<T>::erase(Iterator<T> it1, Iterator<T> it2)
{
    it2--;
    if (it1 < begin() || it1 >= end() || it2 < begin() || it2 >= end())
    {
        throw("Invalid iterator\n");
    }
    if (it2 < it1)
        return;

    int startIDX = it1 - begin();
    int endIDX = it2 - begin();
    int current = 0;

    for (int i = endIDX + 1; i < size(); ++i)
    {
        this->arr[startIDX + current] = this->arr[i];
        current++;
    }
    this->arraySize -= endIDX - startIDX + 1;
}

template <typename T>
Iterator<T> AIVector<T>::end() const
{
    return this->begin() + size();
}

template <typename T>
Iterator<T> AIVector<T>::begin() const
{
    return this->arr;
}

template <typename T>
using Iterator = T *;
template <typename T>
void AIVector<T>::insert(Iterator<T> it, T element)
{
    if (it < begin() || it >= end())
    {
        throw("Invalid iterator\n");
    }
    this->push_back(0);
    int Idx = it - begin();
    cout << "IDX->" << Idx << '\n';

    for (int i = size() - 1; i > Idx; --i)
    {
        this->arr[i] = arr[i - 1];
    }
    this->arr[Idx] = element;
}

#endif // ASS_3_AIVECTOR_H
