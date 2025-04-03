#include "PmergeMe.hpp"
#include <vector>
#include <iomanip>

bool	isNumber(std::string s) {
	if (s.empty())
    {	
        return false;
    }
	size_t	i = 0;
	if (s[i] == '+')
	{
        i++;
    }
    if (i == s.length())
    {
		return (false);
    }   
	while (i < s.length())
    {
		if (!isdigit(s[i]))
	    {
            return (false);
        }
            i++;
    }
	return (true);
}

template<typename Container>
Container	parseInput(int argc, char **argv)
{
	Container	result;

	for (int i = 1; i < argc; i++)
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
		result.push_back(static_cast<typename Container::value_type>(n));
	}
	return result;
}

int main(int argc, char* argv[])
{
	try
	{
		std::vector<int>	vec = parseInput<std::vector<int> >(argc, argv);
		std::deque<int>		deq = parseInput<std::deque<int> >(argc, argv);


		std::cout << std::setw(10) << "Before: ";
		for (int i = 1; i < argc; i++)
			std::cout << argv[i] << " ";
		std::cout << std::endl;

		std::sort(vec.begin(), vec.end());

		std::cout << std::setw(10) << "After: ";
		for (size_t i = 0; i < vec.size(); i++)
			std::cout << vec[i] << " ";
		std::cout << std::endl;

		PmergeMe<std::vector<int> >	msVector(vec.begin(), vec.end());
		msVector.mergeSort(argc);

		PmergeMe<std::deque<int> >	msDeque(deq.begin(), deq.end());
		msDeque.mergeSort(argc);

		// msDeque.printOut();


	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
