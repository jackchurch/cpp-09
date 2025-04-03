#pragma once
#include <vector>
#include <list>
#include <cmath>
#include <iostream>
#include <iomanip>

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
        
        // Sort into sets:
        void    makePairs(Container& startSequence);
        void    setMaxPairs(int argc);
        
        // Merge sets into final list
        void    makeMainAndPend();
        void    beginMergin();
        void    goMerge(int k, int* jPrev);
        void    setJacobsthalNumberIndex(int* j, int* jPrev, int* jPrevPrev);
        void    clearPMain();
        void    preamble(double duration);
        std::vector<std::pair<int, int> >::iterator&  
        binarySearch( 
            int needle, 
            std::vector<std::pair<int, int> >::iterator& mainLeftIT, 
            std::vector<std::pair<int, int> >::iterator& mainRightIT,
            std::vector<std::pair<int, int> >::iterator& mainMidIT);
            
            // Orthodox conanoical
            public:
                PmergeMe();
                ~PmergeMe();
                PmergeMe(const PmergeMe& orignal);
                PmergeMe& operator=(const PmergeMe& orignal);

                template <typename Iter>
                PmergeMe(Iter begin, Iter end);

                void    printOut();
                void    mergeSort(int argc);
    };


bool	isNumber(std::string s);
void    parseInput(int argc, char* argv[]);


#include "PmergeMe.tpp"


