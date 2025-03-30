#pragma once

#include <iostream>
#include <set>


// Cannot use map ordeque
// Use vector and list

// template<typename Container>
class   PmergeMe
{
    private:
        std::vector<int>   _data;
    
    public:
        // Default orthodox
        PmergeMe();
        ~PmergeMe();
        PmergeMe& operator=(const PmergeMe& orignal);
        PmergeMe(const PmergeMe& orignal);

        
    
}

