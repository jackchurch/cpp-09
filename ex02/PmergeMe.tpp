#include "PmergeMe.hpp"

// Orthodox conanoical

template<typename Container>
PmergeMe<Container>::PmergeMe(){};

template<typename Container>
PmergeMe<Container>::~PmergeMe(){};

template<typename Container>
PmergeMe<Container>::PmergeMe(const PmergeMe& orignal)
{
    this->_data = orignal._data;
}

template<typename Container>
PmergeMe<Container>& PmergeMe<Container>::operator=(const PmergeMe& orignal)
{
    this->_data = orignal._data;
    return (*this);
}

template <typename Container>
void PmergeMe<Container>::parseInput(int argc, char *argv[])
{
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

template<typename Container>
void PmergeMe<Container>::printOut()
{
    for (int i = 0; i < (static_cast<typename Container::value_type>(this->_data.size())); i++)
        std::cout << _data[i] << " ";
    std::cout << std::endl;
}