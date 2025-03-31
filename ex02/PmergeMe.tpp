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
}

template <typename Container>
void    PmergeMe<Container>::makePairs(int iterationNumber, Container& startSequence, Container& leftover)
{
   // pair<b, a>
    //       a1 -- a2 -- a3
    //      /     /      /
    //    b1    b2     b3      b4(leftover)
    
    typename Container::iterator        leftIT = _data.begin();
    while (leftIT != _data.end())
    {   
        typename Container::iterator    rightIT = leftIT;
        std::advance(rightIT, iterationNumber);
        if (rightIT != _data.end())
        {
            startSequence.push_back(std::min(*leftIT, *rightIT)); // b
            startSequence.push_back(std::max(*leftIT, *rightIT)); // a
            std::advance(leftIT, iterationNumber * 2);
        }
        else
        {
            leftover.push_back(std::max(*leftIT, *rightIT));
            break ;
        }
    }
    this->_data = startSequence;
    this->_leftovers = leftover;
}

template <typename Container>
void    PmergeMe<Container>::setMaxPairs(int argc)
{
    int power = 1;
    while(power < argc)
    {
        power*=2;
    }
    power/=2;
    this->_maxPairs = std::log2(power);
}

template <typename Container>
void    PmergeMe<Container>::mergeSort()
{
    unsigned int iterationNumber = 1;
    Container   startSequence;
    Container   leftovers;

    if (_data.size() <= 1)
    return ;

    if (iterationNumber != this->_maxPairs)
    {
        makePairs(iterationNumber, startSequence, leftovers);
        iterationNumber++;
    }

    
 
}