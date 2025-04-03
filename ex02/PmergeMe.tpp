#include "PmergeMe.hpp"

// Orthodox conanoical

template <typename Container>
PmergeMe<Container>::PmergeMe(){};

template<typename Container>
PmergeMe<Container>::~PmergeMe(){};

template <typename Container>
PmergeMe<Container>::PmergeMe(const PmergeMe& orignal)
{
    this->_data = orignal._data;
}

template <typename Container>
PmergeMe<Container>& PmergeMe<Container>::operator=(const PmergeMe& orignal)
{
    this->_data = orignal._data;
    return (*this);
}



template <typename Container>
void PmergeMe<Container>::parseInput(int argc, char *argv[])
{
    setMaxPairs(argc);
    int    i = 1;
    while (i < argc)
    {
        if (!isNumber(argv[i]))
        {
            throw std::runtime_error("Error: only input positive integers");
        }
        errno = 0;
		char	*endptr;
		long	n = std::strtol(argv[i], &endptr, 10);
		if (errno == ERANGE || n > INT_MAX || n < INT_MIN)
        {
			throw std::runtime_error("Error: number out of range");
        }
        this->_data.push_back(static_cast<typename Container::value_type>(n));

        i++;
    }


}

template <typename Container>
void PmergeMe<Container>::printOut()
{
    for (int i = 0; i < (static_cast<typename Container::value_type>(this->_data.size())); i++)
        std::cout << _data[i] << " ";
    std::cout << std::endl;
    for (int i = 0; i < (static_cast<typename Container::value_type>(this->_leftovers.size())); i++)
        std::cout << _leftovers[i].second << " ";
    std::cout << std::endl;

}

template <typename Container>
void    PmergeMe<Container>::makePairs(Container& startSequence)
{
   // pair<b, a>
    //       a1 -- a2 -- a3
    //      /     /      /
    //    b1    b2     b3      b4(leftover)

    // leftover<iterationNumber, number>
    //
    //  leftover(1, 6) -> this is the only item expected as iteration is 1
    //  leftover(3, 7) -> expect upto 3 items as iteration is 3
    //  leftover(3, 65)    
    //  leftover(4, 4) -> expect upto 4 items as iteration is 4
    //  leftover(4, 7)
    //  leftover(4, 2)
    //  leftover(4, 65)

    typename Container::iterator    leftIT = _data.begin();
    _incrementAmout = std::pow(2, _iterationNumber);
    while (leftIT != _data.end())
    {
        typename Container::iterator    rightIT = leftIT;
        typename Container::iterator    leftLimit = leftIT;
        std::advance(rightIT, _incrementAmout);
        typename Container::iterator    rightLimit = rightIT;
        // 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6
        //         L   R 
        std::advance(leftLimit, _incrementAmout - 1);
        std::advance(rightLimit, _incrementAmout - 1);

        if (rightIT != _data.end())
        {
            if (*rightLimit < *leftLimit)
            {
                typename Container::iterator    tempIT = rightIT;
                while (tempIT != rightLimit)
                {
                    startSequence.push_back(*tempIT); //b
                    std::advance(tempIT, 1);
                }
                startSequence.push_back(*tempIT);

                tempIT = leftIT;
                while (tempIT != leftLimit)
                {
                    startSequence.push_back(*tempIT); //a
                    std::advance(tempIT, 1);
                }
                startSequence.push_back(*tempIT);
            }
            else
            {
                typename Container::iterator    tempIT = leftIT;
                while (tempIT != leftLimit)
                {
                    startSequence.push_back(*tempIT); //a
                    std::advance(tempIT, 1);
                }
                startSequence.push_back(*tempIT);
                
                tempIT = rightIT;
                while (tempIT != rightLimit)
                {
                    startSequence.push_back(*tempIT); //b
                    std::advance(tempIT, 1);
                }
                startSequence.push_back(*tempIT);
            }
            std::advance(leftIT, _incrementAmout * 2);
            std::advance(rightIT, _incrementAmout * 2);
            if (rightIT == _data.end() || rightIT > _data.end()) // right iteator has gathered all the data, collect leftovers
            {
                while (leftIT != _data.end() && leftIT < _data.end())
                {
                    this->_leftovers.push_back(std::make_pair(_iterationNumber, *leftIT));
                    std::advance(leftIT, 1);
                }
                break ;
            }
        }
        else
        {
            std::advance(leftIT, _incrementAmout - 1);
            while (leftIT != _data.end())
            {
                this->_leftovers.push_back(std::make_pair(_iterationNumber, *leftIT));
                std::advance(leftIT, 1);
            }
            break ;
        }
    }
    this->_data = startSequence;
}

template <typename Container>
void    PmergeMe<Container>::setMaxPairs(int argc)
{
    int power = 1;
    while(power < argc - 1)
    {
        power*=2;
    }
    power/=2;
    this->_maxIteration = std::log2(power);
}

template <typename Container>
void    PmergeMe<Container>::mergeSort()
{
    this->_iterationNumber = 0;
    Container   startSequence;

    if (_data.size() <= 1)
    return ;

    while (this->_iterationNumber != this->_maxIteration)
    {
        startSequence.clear();
        makePairs(startSequence);
        this->_iterationNumber++;
    }
    startSequence.clear();
}

template <typename Container>
void PmergeMe<Container>::makeMainAndPend()
{
    int     bNumber     = 1;
    int     numberInSet = 0;
    int     setsMade    = 0;

    typename Container::iterator dataIT = _data.begin();
    typename Container::iterator beginIT = _data.begin();

    this->_NumberOfSets = _data.size() / (_maxNumbersPerSet); //4 = 16 / 4
    // this->_iterationNumber--;
    // _maxNumbersPerSet = _data.size() / _NumberOfSets;
    while (dataIT != _data.end())
    {
        if (setsMade == 0) // Do inital b1 set:
        {
            while (numberInSet < _maxNumbersPerSet)
            {
                _pMain.push_back(std::make_pair(bNumber * -1, *dataIT));
                std::advance(dataIT, 1);
                numberInSet++;
            }
            numberInSet = 0;
            setsMade = 1;
            continue ;
        }
        while (numberInSet < _maxNumbersPerSet)
        {
            if (bNumber > 0)
                _pMain.push_back(std::make_pair(bNumber, *dataIT));
            else
                _pend.push_back(std::make_pair(bNumber, *dataIT));

            std::advance(dataIT, 1);
            numberInSet++;
        }
        if (bNumber < 0)
        {
            bNumber *= -1;
        }
        else
        {
            bNumber++;
            bNumber *= -1;
        }
        numberInSet = 0;
        setsMade++;
    }
    _data.erase(beginIT, dataIT);
    if (setsMade == _NumberOfSets)
    {
        if (bNumber > 0)
            bNumber *= -1;
        std::vector<std::pair<int, int> >::iterator leftLoIT = _leftovers.begin();
        while (leftLoIT != _leftovers.end() && leftLoIT < _leftovers.end())
        {
            if (leftLoIT->first != static_cast<int>(_iterationNumber))
            {
                std::advance(leftLoIT, 1);
                continue ;
            }

            // if leftOver is from this iteration
            if (leftLoIT->first == static_cast<int>(_iterationNumber))
            {
                std::vector<std::pair<int, int> >::iterator rightLoIT = leftLoIT;
                std::vector<std::pair<int, int> >::iterator pendIT = _pend.begin();
                std::vector<std::pair<int, int> >::iterator pendEndIT = _pend.end();
                // Make rightLoIT last of this set
                std::advance(rightLoIT, _incrementAmout);
                _pend.insert(pendEndIT, leftLoIT, rightLoIT);
                _leftovers.erase(leftLoIT, rightLoIT);
                pendEndIT = _pend.end();
                advance(pendEndIT, _incrementAmout * -1);
                // Make left the next set or end ready for the next round of this while loop. 
                leftLoIT = rightLoIT;
                // update b number for new _pend
                while (pendEndIT != _pend.end())
                {
                    pendEndIT->first = bNumber;
                    std::advance(pendEndIT, 1);
                }
                bNumber--;
            }
        }            
    }
}

template <typename Container>
void    PmergeMe<Container>::clearPMain()
{
    this->_startingSequence.clear();
    std::vector<std::pair<int, int> >::iterator mainIT = _pMain.begin();

    while (mainIT != _pMain.end())
    {
        _data.push_back(mainIT->second);
        std::advance(mainIT, 1);
    }
    _pMain.clear();
    _pend.clear();
}

/*
PrevPrev = 0
Prev = 1
j = 1 + 0*2 = 1

PP = 1
P = 1
j = 1 + 2*1 = 3

PP = 1
P = 3
j = 3 + 2*1 = 5

*/
// 0 1 1 3 5 11 21
template<typename Container>
void	PmergeMe<Container>::setJacobsthalNumberIndex(int* j, int* jPrev, int* jPrevPrev)
{
    if (*j < 0)
    {
        *j = 1;
        return ;
    }
    else
    {
        *jPrevPrev = *jPrev; // 0  1  1  3  5
        *jPrev = *j; // 0  1  1  3  5  11
        *j = *jPrev + *jPrevPrev + *jPrevPrev; //  0  1  1  3  5  11
    }
}

template <typename Container>
std::vector<std::pair<int, int> >::iterator& 
    PmergeMe<Container>::binarySearch( 
        int needle, 
        std::vector<std::pair<int, int> >::iterator& mainLeftIT, 
        std::vector<std::pair<int, int> >::iterator& mainRightIT,
        std::vector<std::pair<int, int> >::iterator& mainMidIT)
{
    while (std::distance(mainLeftIT, mainRightIT) > 0)
    {
        mainMidIT = mainLeftIT;
        int counter = 0;
        while (mainLeftIT != mainRightIT)
        {
            std::advance(mainLeftIT, _incrementAmout);
            counter++;
        }
        std::advance(mainLeftIT, _incrementAmout * counter * -1);
        // Make halfway  if j = 3, mid = 1. remember this will include -1, +1, +2 but not +3
        // int halfway = numberOfSetsToUpperBound / 2;;
        // this->_NumberOfSets = _pMain.size() / (_maxNumbersPerSet);
        // int distance = (std::distance(mainLeftIT, mainRightIT));
        // int numberOfSetsInpMain = (distance / this->_NumberOfSets);
        // int halfway = numberOfSetsInpMain / 2;
        int halfway = counter / 2;
        std::advance(mainMidIT, halfway * _incrementAmout); // go to first value of mid set. 

        if (needle == ((_incrementAmout - 1 + mainMidIT)->second)) // Should never happen
            return (mainMidIT);
        if (needle > ((_incrementAmout - 1 + mainMidIT)->second)) // if our x is > than mid point, it must be in the right half
        {
                mainLeftIT = mainMidIT + _incrementAmout;
                // if (std::distance(mainLeftIT, mainRightIT)  _maxNumbersPerSet)
                // {
                //     return (mainRightIT);
                // }
        }
        else // it is int the left half
            mainRightIT = mainMidIT;
    }
    return (mainLeftIT);
}

template <typename Container>
void PmergeMe<Container>::goMerge(int j, int* jPrev)
{
    if (_pend.size() <= 0)
    {
        return ;
    }
    if (j == 1)
    {
        return ;
    }
    // One loop will move a set from pend to main. 
    // All loops will move all sets for this iteration. 
    while (j > *jPrev)
    {       
        if (_pend.size() <= 0)
        {
            return ;
        }
        if (j == 1)
        {
            return ;
        }
        std::vector<std::pair<int, int> >::iterator insertPosition = _pMain.begin();
        std::vector<std::pair<int, int> >::iterator mainLeftIT = _pMain.begin();

        // Find pend to add
        std::vector<std::pair<int, int> >::iterator pendIT = _pend.begin();
        std::vector<std::pair<int, int> >::iterator pendEnd = _pend.end();
        std::advance(pendEnd, -1);
        
        // Locate j number in b-sequence to merge
        while (std::abs(pendIT->first) != j && pendIT != _pend.end() && pendIT < _pend.end())
        {
            std::advance(pendIT, _incrementAmout);
        }
        if (pendIT == _pend.end() && std::abs(pendIT->first) != j)
        {
            j--;
            continue ;
        }

        pendEnd = pendIT;
        std::advance(pendEnd, _maxNumbersPerSet - 1);
        
        // Locate boundry right
        // j is b-sequence, j is a-sequence
        // if j is 3, then it is b3: 
        // Search limieted to -1, 1, -2, 2. Cannot be more than a3. 
        // Find half way point for -1, 1 and 2
        // Loop until a3 is found for b3's upperbound.
        // the b number wll always be smaller than the a number. 
        std::vector<std::pair<int, int> >::iterator mainRightIT = mainLeftIT;
        // int jIfVectorEndReached;
        // jIfVectorEndReached = 0;
        while (std::abs(mainRightIT->first) != j && mainRightIT != _pMain.end() &&  mainRightIT < _pMain.end())
        {
            // jIfVectorEndReached++;
            std::advance(mainRightIT, _maxNumbersPerSet);
        }
        if (std::abs(mainRightIT->first) != j && mainRightIT == _pMain.end())
        {
            std::cout << "HI" << std::endl;
        }
        std::vector<std::pair<int, int> >::iterator mainMidIT = _pMain.begin();
        // Search 1 set
        insertPosition = binarySearch(pendEnd->second, mainLeftIT, mainRightIT, mainMidIT);
        _pMain.insert(insertPosition, pendIT, pendEnd + 1);
        // std::advance(pendIT, -1);
        for (int i = 0; i < _incrementAmout; i++)
        {
            std::cout << pendIT->first << " : " << pendIT->second << std::endl;
            _pend.erase(pendIT);
        }

        _NumberOfSets++;
        
        j--;
    }
}

// 0 1 1 3 5 11 21
template <typename Container>
void PmergeMe<Container>::beginMergin()
{
    // int             i = 1;
    // unsigned int    setsMade = 0;
    _maxNumbersPerSet = _data.size() / 2;

    // While:
    // Make main and pend from _data and leftovers. 
    while (_iterationNumber > 0)
    {
        _iterationNumber--;
        _incrementAmout = std::pow(2, (_iterationNumber));
        makeMainAndPend();
        int j = -1;
        int jPrev = 1;
        int jPrevPrev = 0;

        // While Pend still has data to move into main. 
        // The main and pend sequence are created above our of this loop

        while (_pend.size() > 0)
        {
            setJacobsthalNumberIndex(&j, &jPrev, &jPrevPrev);
            // Begin merging from j
            goMerge(j, &jPrev);
        }
        _maxNumbersPerSet /= 2;
        clearPMain();

    }
}

// 39 42 2 45 23 40 11 61          5 18 38 51 52 66 15 86
// 2 sets b1 and a1
