#include "RPN.hpp"

RPN::RPN() {}
RPN::~RPN() {}

RPN::RPN(const RPN & orignal)
{
    this->_stack = orignal._stack;
}

RPN &RPN::operator=(const RPN& orignal)
{
    this->_stack = orignal._stack;
    return *this;
}

bool RPN::isOperator(std::string s)
{
    if (s.compare("+") || s.compare("-") 
    || s.compare("*") || s.compare("/"))
    {
        return (true);
    }
    return (false);
}

bool    RPN::doCalculation(std::string s)
{
    double     left;
    double     right;

    // Try to convert stack char in to double
    try
    {
        std::istringstream (s) >> right;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error: " << s << " is not a number." << std::endl;;
    }
    
    this->_stack.pop();

    // Try to convert stack char in to double
    try
    {
        std::istringstream (s) >> left;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error: " << s << " is not a number." << std::endl;;
    }

    this->_stack.pop();

    // What is the operator
    if (s.compare("+"))
    {
        this->_stack.push(left + right);
    }
    else if (s.compare("-"))
    {
        this->_stack.push(left - right);
    }
    else if (s.compare("*"))
    {
        this->_stack.push(left * right);
    }
    else
    {
        if (right == 0)
        {
            std::cerr << "Error: cannot divide by 0" << std::endl;
            return (false);   
        }
        this->_stack.push(left / right);
    }
    return (true);
}


int RPN::calculate(int argc, char* argv[])
{
    if (argc <= 3)
    {
        std::cerr << "Error" << std::endl;
        return (1);
    }

    std::stringstream ss(argv[1]);
    std::string token;
    int i = 0;
    while (ss >> token)
    {
        std::cout << i << std::endl;
        if (token.length() != 1)
        {
            std::cerr << "Error" << std::endl;
            return (1);
        }
        if (isOperator(token) == true)
        {
            if (this->_stack.size() <= 1)
            {
                std::cerr << "Error: not enough numbers for calculation." << std::endl;
                return (1);
            }
            if (doCalculation(token) == false)
            {
                std::cerr << "Error: unknown calculation error." << std::endl;
                return (1);
            }
        }
        try
        {
            this->_stack.push(std::atoi(token.c_str()));
            std::cout << "SGACK" << this->_stack.top() << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << "Error: string to interger." << std::endl;
        }
    }
    return (0);
}
