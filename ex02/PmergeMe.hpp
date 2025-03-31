#pragma once
#include <vector>
#include <list>
#include <cmath>
#include <iostream>

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

template <typename Container>
class PmergeMe
{
    private:
       Container    _data;
       Container    _leftovers;
       unsigned int _maxPairs;
    // Container   _data;
    // Orthodox conanoical
    public:
        PmergeMe();
        ~PmergeMe();
        PmergeMe(const PmergeMe& orignal);
        PmergeMe& operator=(const PmergeMe& orignal);

        void    parseInput(int argc, char* argv[]);
        void    printOut();
        void    mergeSort();
        void    makePairs(int iterationNumber, Container& startSequence, Container& leftover);
        void    setMaxPairs(int argc);

    };

bool	isNumber(std::string s);


#include "PmergeMe.tpp"


