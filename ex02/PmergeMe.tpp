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
void    PmergeMe<Container>::makePairs(int iterationNumber, Container& startSequence)
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
    int     incrementAmout = std::pow(2, iterationNumber);
    while (leftIT != _data.end())
    {
        typename Container::iterator    rightIT = leftIT;
        typename Container::iterator    leftLimit = leftIT;
        std::advance(rightIT, incrementAmout);
        typename Container::iterator    rightLimit = rightIT;
        // 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6
        //         L   R 
        std::advance(leftLimit, incrementAmout - 1);
        std::advance(rightLimit, incrementAmout - 1);

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
            std::advance(leftIT, incrementAmout * 2);
            std::advance(rightIT, incrementAmout * 2);
            if (rightIT == _data.end() || rightIT > _data.end()) // right iteator has gathered all the data, collect leftovers
            {
                while (leftIT != _data.end() && leftIT < _data.end())
                {
                    this->_leftovers.push_back(std::make_pair(iterationNumber, *leftIT));
                    std::advance(leftIT, 1);
                }
                break ;
            }
    }
        else
        {
            std::advance(leftIT, incrementAmout - 1);
            while (leftIT != _data.end())
            {
                this->_leftovers.push_back(std::make_pair(iterationNumber, *leftIT));
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
    unsigned int iterationNumber = 0;
    Container   startSequence;

    if (_data.size() <= 1)
    return ;

    while (iterationNumber != this->_maxPairs)
    {
        startSequence.clear();
        makePairs(iterationNumber, startSequence);
        iterationNumber++;
    }
    startSequence.clear();

    
 
}