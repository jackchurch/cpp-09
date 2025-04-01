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
                    this->_leftovers.push_back(std::make_pair(_iterationNumber + 1, *leftIT));
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
                this->_leftovers.push_back(std::make_pair(_iterationNumber + 1, *leftIT));
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
    this->_maxPairs = std::log2(power);
}

template <typename Container>
void    PmergeMe<Container>::mergeSort()
{
    this->_iterationNumber = 0;
    Container   startSequence;

    if (_data.size() <= 1)
    return ;

    while (this->_iterationNumber != this->_maxPairs)
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

    typename Container::iterator it = _data.begin();
    this->_NumberOfSets = _data.size() / _iterationNumber; //4 = 16 / 4
    this->_iterationNumber--;
    _maxNumbersPerSet = _data.size() / _NumberOfSets;
    while (it != _data.end())
    {
        if (setsMade == 0) // Do inital b1 set:
        {
            while (numberInSet < _maxNumbersPerSet)
            {
                _pMain.push_back(std::make_pair(bNumber * -1, *it));
                std::advance(it, 1);
                numberInSet++;
            }
            numberInSet = 0;
            setsMade = 1;
            continue ;
        }

        while (numberInSet < _maxNumbersPerSet)
        {
            if (bNumber > 0)
                _pMain.push_back(std::make_pair(bNumber, *it));
            else
                _pend.push_back(std::make_pair(bNumber, *it));

            std::advance(it, 1);
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
    if (setsMade == _NumberOfSets)
    {
        if (bNumber > 0)
        bNumber *= -1;
        std::vector<std::pair<int, int> >::iterator it = _leftovers.begin();
        numberInSet = 0;
        while (it != _leftovers.end())
        {
            if (it->first == static_cast<int>(_iterationNumber))
            {
                if (numberInSet < _maxNumbersPerSet)
                {
                    _pend.push_back(std::make_pair(bNumber, it->second));
                    numberInSet++;
                }
                if (numberInSet == _maxNumbersPerSet)
                {
                    bNumber--;
                }
            }
            std::advance(it, 1);
        }            
    }
}

// 0 1 1 3 5 11 21
template<typename Container>
void	PmergeMe<Container>::setJacobsthalNumberIndex(int* j, int* jPrev, int* jPrevPrev)
{
    *j = *jPrev + *jPrevPrev + *jPrevPrev; // 3  5  11
    *jPrevPrev = *jPrev; // 1  3  5
    *jPrev = *j; // 3  5  11
}

template <typename Container>
std::vector<std::pair<int, int> >::iterator& 
    PmergeMe<Container>::binarySearch( 
        std::vector<std::pair<int, int> >::iterator& pendEnd, 
        std::vector<std::pair<int, int> >::iterator& mainLeftIT, 
        std::vector<std::pair<int, int> >::iterator& mainRightIT, 
        int negJ)
{
    // negJ is b-sequence, j is a-sequence
    // if negJ is -3 then j is 3. Search limieted to -1, 1, -2, 2. Cannot be more than 3. 
    // Find half way point for -1, 1 and 2
    // Loop until a3 is found for b3's upperbound.
    if ((negJ * -1) < mainRightIT->first)
    {
        while (negJ * -1 != mainRightIT->first)
        {
            std::advance(mainRightIT, _maxNumbersPerSet * -1);
        }
    }
    
    while (std::distance(mainLeftIT, mainRightIT) > 3)
    {
        std::vector<std::pair<int, int> >::iterator mainMidIT = _pMain.begin();
        // Make halfway  if j = 3, mid = 1. remember this will include -1, +1, +2 but not +3
        // int halfway = numberOfSetsToUpperBound / 2;
        int distance = std::distance(mainLeftIT, mainRightIT) + 1;
        int numberOfSetsInpMain = (distance / _maxNumbersPerSet);
        int halfway = numberOfSetsInpMain / 2;
        if (halfway != 0)
            std::advance(mainMidIT, halfway * (_incrementAmout - 1)); // go to last value of mid set. 
        else
            std::advance(mainMidIT, _incrementAmout - 1); // go to last value of mid set. 
        if (mainMidIT == mainRightIT)
        {
            return (mainLeftIT);
        }
        if (pendEnd->second > mainMidIT->second)
        {
            // In the second half, left search area will start at current mid. 
            mainLeftIT = mainMidIT;
            // increment by 1 as it was greater than the current mid which means it isn't mid. 
            std::advance(mainRightIT, (_iterationNumber * -1));
        }
        else
        {
            // it is in the left half. right search area will end at curent mid. 
            // but not minus one set as it could be the old mid/new right where we insert. 
            mainRightIT = mainMidIT;
        }
    }
    return (mainLeftIT);
}

template <typename Container>
void PmergeMe<Container>::goMerge(int k, int jPrevPrev)
{
    int negJ = k * -1;
    int negJPrev = jPrevPrev * -1;

    std::vector<std::pair<int, int> >::iterator pendIT = _pend.begin();
    std::vector<std::pair<int, int> >::iterator pendEnd = _pend.end();
    std::vector<std::pair<int, int> >::iterator mainLeftIT = _pMain.begin();
    std::vector<std::pair<int, int> >::iterator mainRightIT = _pMain.end();
    std::vector<std::pair<int, int> >::iterator insertPosition;
    std::advance(mainRightIT, -1);
    std::advance(pendEnd, -1);

    // Only go down from current J to 1 before prev J
    // There might still be more b-seqences set to process but that
    // Will happen on a loop out of this loop. 
    while (negJ < negJPrev)
    {
        pendIT = _pend.begin();
        pendEnd = _pend.end();
        std::advance(pendEnd, -1);
        while (pendIT->first != negJ && pendIT != pendEnd)
        {
            std::advance(pendIT, 1);
        }
        if (pendIT->first == negJ)
        {
            pendEnd = pendIT;
            std::advance(pendEnd, _maxNumbersPerSet - 1);
            insertPosition = binarySearch(pendEnd, mainLeftIT, mainRightIT, negJ);
            _pMain.insert(insertPosition, pendIT, pendEnd + 1);
            _pend.erase(pendIT, pendEnd + 1);
        }
        negJ++; 
        // if using b-sequence, this would normaly decrement, but we are using negative numbers for b-sequence, so increment to previous -J nubmer
        // -3 becomes -2. negJPrev is -1 for the first function iteration. 
    }
}

// 0 1 1 3 5 11 21
template <typename Container>
void PmergeMe<Container>::beginMergin()
{
    // int             i = 1;
    // unsigned int    setsMade = 0;

    // While:
    // Make main and pend from _data and leftovers. 
    while (_iterationNumber >= 0)
    {
        makeMainAndPend();
        int j = 0;
        int jPrev = 1;
        int jPrevPrev = 1;

        _iterationNumber--;
        _incrementAmout = std::pow(2, _iterationNumber);

        // While Pend still has data to move into main. 
        // The main and pend sequence are created above our of this loop
        while (_pend.size() > 0)
        {
            setJacobsthalNumberIndex(&j, &jPrev, &jPrevPrev);
            int k = j;
            // While, will stop before the previous Jacobsthal Number.
            // I had to set the jPrev to the current. Don't worry about it.
            // k will be the current set to merge. 
            while (k > jPrevPrev)
            {
                goMerge(k, jPrevPrev);
                k--;
            }
        }
    }
}

// 39 42 2 45 23 40 11 61          5 18 38 51 52 66 15 86
// 2 sets b1 and a1
