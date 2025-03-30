#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {}

PmergeMe &PmergeMe::operator=(const PmergeMe &orignal)
{
    _data = orignal._data;
}

PmergeMe::PmergeMe(const PmergeMe &orignal)
{
    _data = orignal._data;
}
