#include "BitcoinExchange.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    std::cout << "\n\n\n### Begin Ex00 ####\n\n" << std::endl;

    if (argc != 2)
    {
        std::cerr << "input file not found. Usage: ./bit <filename>" << std::endl;
        return (1);
    }
    
    std::string database = "data.csv";
    std::string userfile = argv[1];

    BitcoinExchange exchange;
    exchange.setupDb(database);
    exchange.openUserFile(userfile);

    std::cout << "\n\n\n### End Ex00 ####\n\n\n" << std::endl;

    return (0);
}