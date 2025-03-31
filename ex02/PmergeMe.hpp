#pragma once
#include <vector>
#include <list>

// class PmergeMe
// {
//     private:

//     // Orthodox conanoical
//     public:
//         PmergeMe();
//         ~PmergeMe();
//         PmergeMe(const PmergeMe& orignal);
//         PmergeMe& operator=(const PmergeMe& orignal);
//         std::vector<int> _vData;
//         std::list<int> _lData;
// };

template <typename T>
class PmergeMe
{
    private:
        // T   _data;
    // Orthodox conanoical
    public:
        PmergeMe();
        ~PmergeMe();
        PmergeMe(const PmergeMe& orignal);
        PmergeMe& operator=(const PmergeMe& orignal);
        T   _data;

};

#include "PmergeMe.tpp"


