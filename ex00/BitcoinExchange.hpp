#pragma once

#include <iostream>
#include <fstream>
#include <istream>
#include <map>
#include <sstream>
#include <iomanip>

class BitcoinExchange
{
    private:
        std::map<std::string, float> _database;

        bool	inputDateIsValid(std::string dateString);
        float	getRateForDate(std::string date) const;
        bool	checkInputAmountUser(std::string String, float &actualAmount);
        bool	checkInputAmountDB(std::string amountString, float &actualAmount);

    public:
        // Orthodox Canonical
        BitcoinExchange();
        BitcoinExchange(BitcoinExchange const & orignal);
        BitcoinExchange &operator=(BitcoinExchange const & orignal);
        ~BitcoinExchange();

        std::string     data;
        void            setupDb(std::string& database);
        void            openUserFile(std::string& userFile);
};
