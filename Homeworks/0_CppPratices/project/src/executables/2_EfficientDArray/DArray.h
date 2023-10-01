#pragma once

#include <iostream>
#include <cassert>
// interfaces of Dynamic Array class DArray
template <class T>
class DArray
{
public:
	DArray(); // default constructor
	DArray(int nSize, T dValue = 0); // set an array with default values
	DArray(const DArray& arr); // copy constructor
	~DArray(); // deconstructor

	void Print() const; // print the elements of the array

	int GetSize() const; // get the size of the array
	void SetSize(int nSize); // set the size of the array

	const T& GetAt(int nIndex) const; // get an element at an index
	void SetAt(int nIndex, T dValue); // set the value of an element

	T& operator[](int nIndex); // overload operator '[]'
	const T& operator[](int nIndex) const; // overload operator '[]'

	void PushBack(T dValue); // add a new element at the end of the array
	void DeleteAt(int nIndex); // delete an element at some index
	void InsertAt(int nIndex, T dValue); // insert a new element at some index

	DArray& operator = (const DArray& arr); //overload operator '='

private:
	T* m_pData; // the pointer to the array memory
	int m_nSize; // the size of the array
	int m_nMax;

private:
	void Init(); // initilize the array
	void Free(); // free the array
	void Reserve(int nSize); // allocate enough memory
};

const size_t ARRAY_SIZE = 64;
// default constructor
template <class T>
DArray<T>::DArray() {
	Init();
}

// set an array with default values
template <class T>
DArray<T>::DArray(int nSize, T dValue) {
	m_nSize = nSize;
	m_nMax = (nSize / ARRAY_SIZE + 1) * ARRAY_SIZE;
	m_pData = new T[m_nMax];
	for (int i = 0; i < m_nSize; i++) {
		m_pData[i] = dValue;
	}
}

template <class T>
DArray<T>::DArray(const DArray<T>& arr)
	: m_nSize(arr.m_nSize), m_pData(new T[arr.m_nMax]), m_nMax(arr.m_nMax) {
	for (int i = 0; i < m_nSize; i++) {
		m_pData[i] = arr.m_pData[i];
	}
}

// deconstructor
template <class T>
DArray<T>::~DArray() {
	Free();
}

// display the elements of the array
template <class T>
void DArray<T>::Print() const {
	std::cout << "size of the heap: " << m_nMax << std::endl;
	std::cout << "size of the array: " << m_nSize << std::endl;
	std::cout << "elements of the array: " << std::endl;
	for (int i = 0; i < m_nSize; i++) {
		std::cout << i << ": " << m_pData[i] << std::endl;
	}
}

// initilize the array
template <class T>
void DArray<T>::Init() {
	m_pData = nullptr;
	m_nSize = 0;
	m_nMax = 0;
}

// free the array
template <class T>
void DArray<T>::Free() {
	delete[] m_pData;
	m_pData = nullptr;
	m_nSize = 0;
	m_nMax = 0;
}

// get the size of the array
template <class T>
int DArray<T>::GetSize() const {
	return m_nSize;
}

// set the size of the array
template <class T>
void DArray<T>::SetSize(int nSize) {
	if (nSize < 0) {
		std::cerr << "invalid size: " << __func__ << std::endl;
		return;
	}
	if (nSize > m_nMax) {
		m_nMax = (nSize / ARRAY_SIZE + 1) * ARRAY_SIZE;
		T* tmp_pData = new T[m_nMax];
		for (int i = 0; i < m_nSize; i++) {
			tmp_pData[i] = m_pData[i];
		}
		//better implementation: memcpy
		delete[] m_pData;
		m_pData = tmp_pData;
	}
	for (int i = m_nSize; i < nSize; i++) {
		m_pData[i] = 0;
	}
	m_nSize = nSize;
}

// get an element at an index
template <class T>
const T& DArray<T>::GetAt(int nIndex) const {
	assert(nIndex >= 0 && nIndex < m_nSize);
	return m_pData[nIndex];
}

// set the value of an element 
template <class T>
void DArray<T>::SetAt(int nIndex, T dValue) {
	assert(nIndex >= 0 && nIndex < m_nSize);
	m_pData[nIndex] = dValue;
}

// overload operator '[]'
template <class T>
T& DArray<T>::operator[](int nIndex) {
	assert(nIndex >= 0 && nIndex < m_nSize);
	return m_pData[nIndex];
}

// overload operator '[]'
template <class T>
const T& DArray<T>::operator[](int nIndex) const {
	assert(nIndex >= 0 && nIndex < m_nSize);
	return m_pData[nIndex];
}

// add a new element at the end of the array
template <class T>
void DArray<T>::PushBack(T dValue) {
	if (m_nSize + 1 > m_nMax) {
		m_nMax += ARRAY_SIZE;
		T* tmp_pData = new T[m_nMax];
		for (int i = 0; i < m_nSize; i++) {
			tmp_pData[i] = m_pData[i];
		}
		delete[] m_pData;
		m_pData = tmp_pData;
	}
	m_pData[m_nSize] = dValue;
	m_nSize++;
}

// delete an element at some index
template <class T>
void DArray<T>::DeleteAt(int nIndex) {
	assert(nIndex >= 0 && nIndex < m_nSize);
	for (int i = nIndex; i < m_nSize - 1; i++) {
		m_pData[i] = m_pData[i + 1];
	}
	m_nSize--;
}

// insert a new element at some index
template <class T>
void DArray<T>::InsertAt(int nIndex, T dValue) {
	assert(nIndex >= 0 && nIndex < m_nSize + 1);
	if (m_nSize + 1 > m_nMax) {
		m_nMax += ARRAY_SIZE;
		T* tmp_pData = new T[m_nMax];
		for (int i = 0; i < m_nSize; i++) {
			tmp_pData[i] = m_pData[i];
		}
		delete[] m_pData;
		m_pData = tmp_pData;
	}
	for (int i = m_nSize - 1; i >= nIndex; i--) {
		m_pData[i + 1] = m_pData[i];
	}
	m_pData[nIndex] = dValue;
	m_nSize++;
}

// overload operator '='
template <class T>
DArray<T>& DArray<T>::operator = (const DArray& arr) {
	delete[] m_pData;
	m_pData = new T[arr.m_nMax];
	m_nSize = arr.m_nSize;
	m_nMax = arr.m_nMax;
	for (int i = 0; i < m_nSize; i++) {
		m_pData[i] = arr.m_pData[i];
	}
	return *this;
}
