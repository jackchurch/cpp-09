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
        Container   _data;
        int         _maxIteration;
        int         _iterationNumber;
        int         _NumberOfSets;
        int         _maxNumbersPerSet;
        int         _incrementAmout;
        int         _mergeIterationNumber;
        int         _mergeNumbersPerSet;

        std::vector<std::pair<int, int> >    _pMain;
        std::vector<std::pair<int, int> >    _pend;
        std::vector<int>                     _startingSequence;
        std::vector<std::pair<int, int> >    _leftovers;    

    // Orthodox conanoical
    public:
        PmergeMe();
        ~PmergeMe();
        PmergeMe(const PmergeMe& orignal);
        PmergeMe& operator=(const PmergeMe& orignal);

        // Sort into sets:
        void    parseInput(int argc, char* argv[]);
        void    printOut();
        void    mergeSort();
        void    makePairs(Container& startSequence);
        void    setMaxPairs(int argc);

        // Merge sets into final list
        void    makeMainAndPend();
        void    beginMergin();
        void    goMerge(int k, int* jPrev);
        void    setJacobsthalNumberIndex(int* j, int* jPrev, int* jPrevPrev);
        void    clearPMain();
        std::vector<std::pair<int, int> >::iterator&  
            binarySearch( 
                int needle, 
                std::vector<std::pair<int, int> >::iterator& mainLeftIT, 
                std::vector<std::pair<int, int> >::iterator& mainRightIT,
                std::vector<std::pair<int, int> >::iterator& mainMidIT);
            
            };


bool	isNumber(std::string s);


#include "PmergeMe.tpp"


