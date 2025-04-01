#include "PmergeMe.hpp"
#include <vector>
int main(int argc, char* argv[])
{
	
	// PmergeMe<std::vector<int> > myVector;
	// myVector._data.push_back(5);
	// PmergeMe myVector;
	// myVector._lData.push_back(5);

	PmergeMe<std::vector<int> > *myVector = new PmergeMe<std::vector<int> >();
	myVector->parseInput(argc, argv);
	myVector->printOut();
	myVector->mergeSort();
	myVector->printOut();
	myVector->beginMergin();
	delete (myVector);

	return (0);
}
