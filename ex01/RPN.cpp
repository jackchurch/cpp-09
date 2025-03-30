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
    return (*this);
}

bool RPN::isOperator(std::string s)
{
    if (s.compare("+") == 0 || s.compare("-") == 0 
    || s.compare("*") == 0 || s.compare("/") == 0)
    {
        return (true);
    }
    return (false);
}

bool    RPN::doCalculation(std::string s)
{
    double     left;
    double     right;

    right = this->_stack.top();
    this->_stack.pop();
    left = this->_stack.top();
    this->_stack.pop();

    switch (s[0])
    {
        case '+':
        {
            this->_stack.push(left + right);
            break ;
        }
        case '-':
        {
            this->_stack.push(left - right);
            break ;
        }
        case '*':
        {
            this->_stack.push(left * right);
            break ;
        }
        case '/':
        {
            if (right == 0)
            {
                std::cerr << "Error: cannot divide by 0" << std::endl;
                exit (1);   
            }
            this->_stack.push(left / right);
            break ;
        }
    }
    return (true);
}

int RPN::calculate(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Error: Operators and operands must be enclosed in quotation marks as one string." << std::endl;
        std::cerr << "Usage including quotes: ./RPN \"5 9 7 / +\""<< std::endl;
        return (1);
    }

    std::istringstream ss(argv[1]);
    std::string token;
    while (ss >> token)
    {
        if (token.length() != 1)
        {
            std::cerr << "Error: Only single digits allowed and operators must be seperated by a space from digits." << std::endl;
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
            continue ;
        }
        if (std::isdigit(token[0]))
        {
            this->_stack.push(std::atoi(token.c_str()));
        }
    }
    std::cout << this->_stack.top() << std::endl;
    return (0);
}
