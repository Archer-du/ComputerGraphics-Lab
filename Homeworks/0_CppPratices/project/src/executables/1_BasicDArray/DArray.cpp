// implementation of class DArray
#include "DArray.h"
#include <iostream>

// default constructor
DArray::DArray() {
	Init();
}

// set an array with default values
DArray::DArray(int nSize, double dValue)
	: m_nSize(nSize), m_pData(new double[nSize])
{
	for (int i = 0; i < nSize; i++) {
		m_pData[i] = dValue;
	}
}

DArray::DArray(const DArray& arr)
	: m_nSize(arr.m_nSize), m_pData(new double[arr.m_nSize])
{
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
	std::cout << "elements of the array: " << std::endl;
	for (int i = 0; i < m_nSize; i++) {
		std::cout << i << ": " << m_pData[i] << std::endl;
	}
}

// initialize the array
void DArray::Init() {
	m_pData = nullptr;
	m_nSize = 0;
}

// free the array
void DArray::Free() {
	delete[] m_pData;
	m_pData = nullptr;
	m_nSize = 0;
}

// get the size of the array
int DArray::GetSize() const {
	return m_nSize;
}

// set the size of the array
void DArray::SetSize(int nSize) {
	if (nSize < m_nSize) {
		std::cerr << "invalid size: " << __func__ << std::endl;
		return;
	}
	double* tmp_pData = new double[nSize];
	for (int i = 0; i < nSize; i++) {
		if (i < m_nSize) {
			tmp_pData[i] = m_pData[i];
		}
		else {
			tmp_pData[i] = 0;
		}
	}
	m_nSize = nSize;
	m_pData = tmp_pData;
}

// get an element at an index
const double& DArray::GetAt(int nIndex) const {
	if (nIndex < 0 || nIndex >= m_nSize) {
		std::cerr << "invalid index: " << __func__ << std::endl;
		return NULL;
	}
	//better implementation: assert(nIndex >= 0 && nIndex < m_nSize);
	return m_pData[nIndex];
}

// set the value of an element 
void DArray::SetAt(int nIndex, double dValue) {
	if (nIndex < 0 || nIndex >= m_nSize) {
		std::cerr << "invalid index: " << __func__ << std::endl;
		return;
	}
	m_pData[nIndex] = dValue;
}

// overload operator '[]'
const double& DArray::operator[](int nIndex) const {
	if (nIndex < 0 || nIndex >= m_nSize) {
		std::cerr << "invalid index: " << __func__ << std::endl;
		return NULL;
	}
	//better implementation: assert(nIndex >= 0 && nIndex < m_nSize);
	return m_pData[nIndex];
}

// add a new element at the end of the array
void DArray::PushBack(double dValue) {
	double* tmp_pData = new double[m_nSize + 1];
	//better implementation: double* pTemp = new double[static_cast<size_t>(m_nSize) - 1];
	tmp_pData[m_nSize] = dValue;
	for (int i = 0; i < m_nSize; i++) {
		tmp_pData[i] = m_pData[i];
	}
	delete[] m_pData;
	m_nSize++;
	m_pData = tmp_pData;
}

// delete an element at some index
void DArray::DeleteAt(int nIndex) {
	if (nIndex < 0 || nIndex >= m_nSize) {
		std::cerr << "invalid index: " << __func__ << std::endl;
		return;
	}
	double* tmp_pData = new double[m_nSize - 1];
	int j = 0;
	for (int i = 0; i < m_nSize; i++) {
		if (i != nIndex) {
			tmp_pData[j] = m_pData[i];
			j++;
		}
	}
	delete[] m_pData;
	m_nSize--;
	m_pData = tmp_pData;
}

// insert a new element at some index
void DArray::InsertAt(int nIndex, double dValue) {
	if (nIndex < 0 || nIndex >= m_nSize + 1) {
		std::cerr << "invalid index: " << __func__ << std::endl;
		return;
	}
	double* tmp_pData = new double[m_nSize + 1];
	int j = 0;
	for (int i = 0; i < m_nSize + 1; i++) {
		if (i != nIndex) {
			tmp_pData[i] = m_pData[j];
			j++;
		}
		else {
			tmp_pData[i] = dValue;
		}
	}
	delete[] m_pData;
	m_nSize++;
	m_pData = tmp_pData;
}

// overload operator '='
DArray& DArray::operator = (const DArray& arr) {
	if (m_nSize > 0) {
		delete[] m_pData;
	}
	m_nSize = arr.m_nSize;
	m_pData = new double[m_nSize];
	for (int i = 0; i < m_nSize; i++) {
		m_pData[i] = arr.m_pData[i];
	}
	return *this;
}
