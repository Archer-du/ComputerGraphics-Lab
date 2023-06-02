// implementation of class DArray
// notice: Allocation strategy differs from task requirements
#include "DArray.h"
#include <iostream>
#include <cassert>

const size_t ARRAY_SIZE = 64;
// default constructor
DArray::DArray() {
	Init();
}

// set an array with default values
DArray::DArray(int nSize, double dValue) {
	m_nSize = nSize;
	m_nMax = (nSize / ARRAY_SIZE + 1) * ARRAY_SIZE;
	m_pData = new double[m_nMax];
	for (int i = 0; i < m_nSize; i++) {
		m_pData[i] = dValue;
	}
}

DArray::DArray(const DArray& arr) 
	: m_nSize(arr.m_nSize), m_pData(new double[arr.m_nMax]), m_nMax(arr.m_nMax) {
	for (int i = 0; i < m_nSize; i++) {
		m_pData[i] = arr.m_pData[i];
	}
}

// deconstructor
DArray::~DArray() {
	Free();
}

// display the elements of the array
void DArray::Print() const {
	std::cout << "size of the heap: " << m_nMax << std::endl;
	std::cout << "size of the array: " << m_nSize << std::endl;
	std::cout << "elements of the array: " << std::endl;
	for (int i = 0; i < m_nSize; i++) {
		std::cout << i << ": " << m_pData[i] << std::endl;
	}
}

// initilize the array
void DArray::Init() {
	m_pData = nullptr;
	m_nSize = 0;
	m_nMax = 0;
}

// free the array
void DArray::Free() {
	delete[] m_pData;
	m_pData = nullptr;
	m_nSize = 0;
	m_nMax = 0;
}

// get the size of the array
int DArray::GetSize() const {
	return m_nSize;
}

// set the size of the array
void DArray::SetSize(int nSize) {
	if (nSize < 0) {
		std::cerr << "invalid size: " << __func__ << std::endl;
		return;
	}
	if (nSize > m_nMax) {
		m_nMax = (nSize / ARRAY_SIZE + 1) * ARRAY_SIZE;
		double* tmp_pData = new double[m_nMax];
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
const double& DArray::GetAt(int nIndex) const {
	assert(nIndex >= 0 && nIndex < m_nSize);
	return m_pData[nIndex];
}

// set the value of an element 
void DArray::SetAt(int nIndex, double dValue) {
	assert(nIndex >= 0 && nIndex < m_nSize);
	m_pData[nIndex] = dValue;
}

// overload operator '[]'
double& DArray::operator[](int nIndex) {
	assert(nIndex >= 0 && nIndex < m_nSize);
	return m_pData[nIndex];
}

// overload operator '[]'
const double& DArray::operator[](int nIndex) const {
	assert(nIndex >= 0 && nIndex < m_nSize);
	return m_pData[nIndex];
}

// add a new element at the end of the array
void DArray::PushBack(double dValue) {
	if (m_nSize + 1 > m_nMax) {
		m_nMax += ARRAY_SIZE;
		double* tmp_pData = new double[m_nMax];
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
void DArray::DeleteAt(int nIndex) {
	assert(nIndex >= 0 && nIndex < m_nSize);
	for (int i = nIndex; i < m_nSize - 1; i++) {
		m_pData[i] = m_pData[i + 1];
	}
	m_nSize--;
}

// insert a new element at some index
void DArray::InsertAt(int nIndex, double dValue) {
	assert(nIndex >= 0 && nIndex < m_nSize + 1);
	if (m_nSize + 1 > m_nMax) {
		m_nMax += ARRAY_SIZE;
		double* tmp_pData = new double[m_nMax];
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
DArray& DArray::operator = (const DArray& arr) {
	delete[] m_pData;
	m_pData = new double[arr.m_nMax];
	m_nSize = arr.m_nSize;
	m_nMax = arr.m_nMax;
	for (int i = 0; i < m_nSize; i++) {
		m_pData[i] = arr.m_pData[i];
	}
	return *this;
}
