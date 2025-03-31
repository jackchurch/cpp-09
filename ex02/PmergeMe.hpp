#pragma once
#include <vector>
#include <list>

class PmergeMe
{
    private:
        std::vector<int> _vData;
        std::list<int> _lData;
    // Orthodox conanoical
    public:
        PmergeMe();
        ~PmergeMe();
        PmergeMe(const PmergeMe& orignal);
        PmergeMe& operator=(const PmergeMe& orignal);
};

// #include "PmergeMe.tpp"