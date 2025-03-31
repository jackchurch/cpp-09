#include "PmergeMe.hpp"
#include <vector>
int main()
{

	PmergeMe<std::vector<int> > myVector;
	myVector._data.push_back(5);
	// PmergeMe myVector;
	// myVector._lData.push_back(5);
	
	return (0);
}
