#include "PmergeMe.hpp"

// Orthodox conanoical

template<typename T>
PmergeMe<T>::PmergeMe(){};

template<typename T>
PmergeMe<T>::~PmergeMe(){};

template<typename T>
PmergeMe<T>::PmergeMe(const PmergeMe& orignal)
{
    this->_data = orignal._data;
}

template<typename T>
PmergeMe<T>& PmergeMe<T>::operator=(const PmergeMe& orignal)
{
    this->_data = orignal._data;
    return (*this);
}