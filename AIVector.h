//
// Created by Ismail Magdy on 06/12/2022.
//

#ifndef ASS_3_AIVECTOR_H
#define ASS_3_AIVECTOR_H
#include <iostream>
//---------------------------------------Headers-------------------------------------------------------------------
using namespace std;
template<typename T>
using iterator = T*;

template<typename T>
class AIVector {
    template<typename type>
    friend std::ostream& operator << (std::ostream& out, ::AIVector<type>);
public:
    // Constructors
    AIVector(int size = 0 );
    AIVector(T*,int n );
    AIVector(const AIVector<T>& other);
    AIVector(AIVector<T>&& other);
    ~AIVector();

    // Assignment
    AIVector<T>& operator=(const AIVector<T>& other);
    AIVector<T>operator=(AIVector<T>&& other);

    // Indexing
    T& operator[](int)const;
    T& operator[](int);

    // getters
    int size()const;
    int capacity()const;
    bool isEmpty()const;

    // reSizing
    void resize(int size);
    void clear();

    // adding , removing elements
    int push_back(const T& element);
    T pop_back();

    // Comparison
    bool operator==(const AIVector<T>& other)const;
    bool operator>(const AIVector<T>& other)const;
    bool operator<(const AIVector<T>& other)const;

    // iterators
    void insert(iterator<T>, T);
    void erase(iterator<T>it);
    void erase(iterator<T>it1, iterator<T>it2);
    iterator<T>begin()const;
    iterator<T>end()const;
private:
    T* arr;
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





//----------------------------------------------------Move Assignment--------------------------------------------------------
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





//----------------------------------------------------Destructor------------------------------------------------------------------

template<typename T>
AIVector<T>::~AIVector() {
    delete[] this->arr;
}




//----------------------------------------------------INDEXING LHS [] --------------------------------------------------------------------

template<typename T>
T &AIVector<T>::operator[](int position){
    if(position<0 || position >= capacity())
        throw ("Out of Bounds\n");
    return arr[position];

}





//----------------------------------------------------INDEXING RHS [] --------------------------------------------------------------------

template<typename T>
T &AIVector<T>::operator[](int position)const{
    if(position<0 || position >= capacity())
        throw ("Out of Bounds\n");
    return arr[position];
}






//---------------------------------------------------- Pop-Back --------------------------------------------------------------------
/**
 * @brief delete last element is the vector 
 *        decrase size by 1 
 * 
 * @tparam T 
 * @return T new size after deleting
 */
template<typename T>
T AIVector<T>::pop_back() {
    if(this->isEmpty())
        throw ("Already Empty vector\n");
    arraySize--;
    return this->arr[size()+1];
}






//---------------------------------------------------- Push-Back --------------------------------------------------------------------
/**
 * @brief add element to the end of the vector 
 *        if allocated capcaity is bigger than size we add to the array
 *        if allocated capcity is smaller we multiply capacity *2 
 * @tparam T 
 * @param element 
 * @return int 
 */
template<typename T>
int AIVector<T>::push_back(const T &element) {
    if(size() >= capacity()){
        int newCapacity = this->size() *2;
        T* doubleSizeArray = new T[newCapacity];
        for (int i = 0; i < this->size(); ++i) {
            doubleSizeArray[i] = this->arr[i];
        }
        doubleSizeArray[this->size()] = element;
        delete[] this->arr;
        arr = doubleSizeArray;
        this->arraySize++;
        this->arrayCapacity = newCapacity;
        doubleSizeArray =NULL;
    }
    else{
        this->arr[arraySize] = element;
        this->arraySize++;
    }
    return size();
}






//---------------------------------------------------- < operator --------------------------------------------------------------------
/**
 * @brief 
 * 
 * @tparam T 
 * @param other 
 * @return true 
 * @return false 
 */
template<typename T>
bool AIVector<T>::operator<(const AIVector<T> &other)const{
    int size  = min(this->size(), other.size());
    for (int i = 0; i < size; ++i) {
        if((*this)[i] < other[i])
            return true;
        if((*this)[i] > other[i])
            return false;
    }
    return false;
}





//---------------------------------------------------- > operator --------------------------------------------------------------------
/**
 * @brief check if elements of first vecotr  is bigger than other vector
 * 
 * @tparam T 
 * @param other 
 * @return true if first diffrent element is bigger than the element in other vector
 * @return false if equal or smaller elements 
 */
template<typename T>
bool AIVector<T>::operator>(const AIVector<T> &other)const {
    int size  = min(this->size(), other.size());
    for (int i = 0; i < size; ++i) {
        if((*this)[i] > other[i])
            return true;
        if((*this)[i] < other[i])
            return false;
    }
    return false;
}








//---------------------------------------------------- ==  Operator--------------------------------------------------------------------

/**
 * @brief  check equality of two vectors
 * 
 * @tparam T 
 * @param other 
 * @return true if two vetors are of same size and data 
 * @return false if two vectors are of diffrent sizes or data
 */
template<typename T>
bool AIVector<T>::operator==(const AIVector <T>&other)const{
    if(this->size() != other.size())
        return false;
    int size = this->size();
    for (int i = 0; i <size; ++i) {
        if((*this)[i] != other[i])
            return false;
    }
    return true;
}






//-------------------------------------------------------Size getter --------------------------------------------------------------------
/**
 * @brief getting number of elements stored in the vector
 * 
 * @tparam T 
 * @return int number of data stored in the vector
 */
template<typename T>
int AIVector<T>::size() const {
    return this->arraySize;
}







//----------------------------------------------------Capacity getter--------------------------------------------------------------------
/**
 * @brief get allocated memory 
 * 
 * @tparam T 
 * @return int number of allocated data 
 */
template<typename T>
int AIVector<T>::capacity() const {
    return this->arrayCapacity;
}





//----------------------------------------------------Empty check--------------------------------------------------------------------
/**
 * @brief determine if there is data stored in the vector
 * 
 * @tparam T 
 * @return true if no elements in the vector
 * @return false if there is elements in the vector
 */
template<typename T>
bool AIVector<T>::isEmpty() const {
    return this->size() == 0;
}








//----------------------------------------------------Resizing--------------------------------------------------------------------
/**
 * @brief resizing the vetor to allocate a smaller or bigger byffer of data
 *         if newSize is smaller we dont delete extra memory to optimize performance
 *         if newSize is bigger we allocate a bigger buffer of data
 * @tparam T 
 * @param newSize 
 */
template<typename T>
void AIVector<T>::resize(int newSize) {
    if(newSize <= this->size()){
        this->arraySize = newSize;
    }
    else{
        T*  newArray = new T[newSize];
        for (int i = 0; i < size(); ++i) {
            newArray[i] = this->arr[i];
        }
        delete[] arr;
        this->arr = newArray;
        this->arraySize = newSize;
        this->arrayCapacity = size();
        newArray =NULL;
    }
}






//----------------------------------------------------Clearing vector--------------------------------------------------------------------
/**
 * @brief clearing all the allocated elements,setting them to their default value 
 *        setting size to 0 
 * 
 * @tparam T 
 */
template<typename T>
void AIVector<T>::clear() {
    for (int i = 0; i < this->size(); ++i) {
        this->arr[i] = T();
    }
    this->arraySize = 0;
}





//----------------------------------------------------Printing--------------------------------------------------------------------

/**
 * @brief   printing the data in the vector 
 * 
 */
template<typename T>
std::ostream &operator<<(std::ostream &out,AIVector<T> vector){
    int size= vector.size();
    for (int i = 0; i <size; ++i) {
        out<<vector.arr[i]<<" ";
    }
    return out;
}







//----------------------------------------------------Erasing one elements--------------------------------------------------------------------

/**
 * @brief function that takes one iterator and erase element at that iterator position if it is valid 
 *        it raises an exception if iterator is unvalid
 * 
 * @tparam Iterator<T> iterator to be erased from the vector 
 */
template<typename T>
using Iterator = T* ;
template<typename T>
void AIVector<T>::erase(Iterator<T> it){
    if(it < begin() || it >= end()){
        throw ("Invalid iterator\n");
    }
    int idx = it - begin();

    for (int i = idx+1; i <this->size(); ++i) {
        this->arr[i-1] = this->arr[i];
    }
    this->arraySize--;
}









//----------------------------------------------------Erasing Range of elements--------------------------------------------------------------------

/**
 * @brief function erasing a range of elements from start iterator up to another  iterator 
 *        it erases an exception if iterator is unvalid 
 * 
 * @tparam Iterator<T>it1 start iterator , Iterator<T>it2 end iterator 
 *         erase from start to end iterator not  including the  end element
 */
template<typename T>
using Iterator = T* ;
template<typename T>
void AIVector<T>::erase(Iterator<T> it1, Iterator<T> it2) {
    it2--;
    if(it1 < begin() || it1 >= end() || it2 < begin() || it2 >= end()){
        throw ("Invalid iterator\n");
    }
    if(it2 < it1)
        return;

    int startIDX = it1 - begin();
    int endIDX = it2 - begin();
    int current = 0 ;

    for (int i = endIDX+1; i < size() ; ++i) {
        this->arr[startIDX + current] = this->arr[i];
        current++;
    }
    this->arraySize -= endIDX - startIDX + 1 ;
}






//---------------------------------------------------- End Iterator--------------------------------------------------------------------

/**
 * @brief function returning iterator after the last element in the vector 
 * 
 * @tparam T 
 * @return Iterator<T>  iterator after last element
 */
template<typename T>
Iterator<T> AIVector<T>::end() const {
    return this->begin()+size();
}







//---------------------------------------------------- Begin Iterator--------------------------------------------------------------------
/**
 * @brief function return itertor at the begining of the data buffer
 *  
 * @tparam T 
 * @return Iterator<T>  iterator at the start 
 */
template<typename T>
Iterator<T> AIVector<T>::begin()const{
    return this->arr;
}







//---------------------------------------------------- Inserting ---------------------------------------------------------------------
/**
 * @brief function Inserting function that takes an iterator, element  and  insert that element  in the vector    
 *        if the iterator is valid and within the vector range  
 * 
 * @tparam T Iterator (pos of insertion)  , T element (element to be inserted)
 */
template<typename T>
using Iterator = T* ;
template<typename T>
void AIVector<T>::insert(Iterator<T> it , T element) {
    if(it < begin() || it >= end()){
        throw ("Invalid iterator\n");
    }
    this->push_back(0);
    int Idx = it - begin();
    cout<<"IDX->"<<Idx<<'\n';

    for (int i = size()-1; i >Idx ; --i) {
        this->arr[i] = arr[i-1];
    }
    this->arr[Idx] = element;
}

#endif //ASS_3_AIVECTOR_H


//------------------------------------------------------------------------------------------------------------------------------------------------
