#include "PmergeMe.hpp"

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
