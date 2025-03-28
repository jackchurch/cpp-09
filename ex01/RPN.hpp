#pragma once

#include <stack>
#include <string>
#include <iostream>
#include <sstream>
#include <cstdlib>

class RPN
{
	private:
		std::stack<float> _stack;
        bool isOperator(std::string s);
        bool    doCalculation(std::string s);
	
	public:
		RPN();
		RPN(const RPN& orignal);
		RPN &operator=(const RPN & orignal);
		~RPN();
        int calculate(int argc, char* argv[]);
};

