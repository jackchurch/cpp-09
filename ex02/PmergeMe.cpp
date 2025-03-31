#include "PmergeMe.hpp"

PmergeMe::PmergeMe(){};

PmergeMe::~PmergeMe(){};

PmergeMe::PmergeMe(const PmergeMe& orignal)
{
    this->_lData = orignal._lData;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& orignal)
{
    this->_lData = orignal._lData;
    return (*this);
}