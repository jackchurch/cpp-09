#pragma once

#include "BitcoinExchange.hpp"

// Orthodox Canonical
BitcoinExchange::BitcoinExchange()
{
    std::map<std::string, float> _database;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy)
{
    this->_database = copy._database;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &copy) 
{
    this->_database = copy._database;
        return (*this);
}

BitcoinExchange::~BitcoinExchange() {}



bool BitcoinExchange::validateDb(std::string &database)
{
    std::string             line;
    std::istringstream      iss(line);
    std::string             dateString;
    Optional<std::string>   optionalDate;
    std::string             amountString;
    Optional<float>         optionalAmount;
    char                    seperator;

    int i = 0;

    std::ifstream   infile(database.c_str());
    if (!infile.is_open())
        throw std::runtime_error("Cannot open database");
    
    std::getline(infile, line);
    if (line != "date,exchange_rate")
    {
        std::cerr << ("Database format is incorrect") << std::endl;
        infile.close();
        return (false);
    }
    
    while(std::getline(infile, line))
    {
        i++;
        iss.str(line);
        if (!(iss >> dateString >> seperator >> amountString) || seperator != ',')
        {
            std::cerr << "Database Error: Line "<< i <<" has bad input => : " << line << std::endl;
            continue ;
        }

        optionalDate = checkInputDate(dateString);
        if (!optionalDate.hasValue())
        {
            std::cerr << "Database Error: Line "<< i <<" has a bad date => : " << dateString << std::endl;
            continue ;
        }

        optionalAmount = checkInputAmount(amountString);
        if (!optionalAmount.hasValue())
        {
            continue ;
        }
        std::string actualDate = <
        _database.insert(std::make_pair(actualDate, actualAmount));        
    }

    infile.close();

    if (_database.size() == 0)
    {
        return (false);
    }

    return (true);
}


void    printBitcoinValue(float btcPrice, float userValue)
{
    float bitcoinValue = btcPrice * userValue;
    std::cout << dateString << " => " << userValue << " => " << bitcoinValue << std::fixed << std::setprecision(2) << std::endl;

}



void BitcoinExchange::openUserFile(std::string &userFile)
{
    std::string             line;
    std::istringstream      iss(line);
    std::string             userDateString;
    std::string             userAmountString;
    Optional<std::string>   actualDate;
    Optional<float>         actualAmount;
    char                    seperator;

    int i = 1;

    std::ifstream   infile(userFile.c_str());
    if (!infile.is_open())
        throw std::runtime_error("Cannot open userfile");
    
    std::getline(infile, line);
    if (line != "date | value")
    {
        std::cerr << ("Userfile format is incorrect") << std::endl;
        infile.close();
        return ;
    }

    while(std::getline(infile, line))
    {
        iss.str(line);
        if (!(iss >> userDateString >> seperator >> userAmountString) || seperator != '|')
        {
            std::cerr << "Error: User input line "<< i <<" has bad input => : " << line << std::endl;
            continue ;
        }

        actualDate = checkInputDate(userDateString);
        if (!actualDate.hasValue())
        {
            std::cerr << "Error: User input line "<< i <<" has a bad date => : " << userDateString << std::endl;
            continue ;
        }
        std::string temp = actualDate;

        actualAmount = checkInputAmount(userAmountString);
        if (!actualDate.hasValue())
        {
            continue ;
        }

        std::map<std::string, float>::iterator it = _database.find(actualDate);
        if (it != _database.end())
        {
            printBitcoinValue(it->second, )
            return (it->second);
        }

    }
}


Optional<float>   BitcoinExchange::checkInputAmount(std::string amountString)
{
    float amount;
    std::string sub;
    if (amountString.back() == 'f')
        sub = amountString.substr(0, amountString.size() - 1);
    else
        sub = amountString;

    try
    {
        amount = std::stod(sub);
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Error: Invalid amount => " << sub << std::endl;
        return ;
    }
    catch (const std::out_of_range &e)
    {
        std::cerr << "Error: Amount out of range => " << sub << std::endl;
        return ;
    }
    if (amount < 0 || amount > 1000)
    {
        std::cerr << "Error: Amount out of range => " << sub << std::endl;
        return ;
    }
    return (amount);
}

Optional<std::string> BitcoinExchange::checkInputDate(std::string dateString)
{
    std::istringstream iss(dateString);
    int     d, m, y;
    char    delim;
    if (iss >> y >> delim >> m >> delim >> d) 
    {
        struct tm date;
        std::memset(&date, 0, sizeof(date));
        date.tm_mday = d;
        date.tm_mon = m - 1;
        date.tm_year = y - 1900;
        date.tm_isdst = -1;

        // convet into epoch and back so this doesn't happen...
        // 2012-01-100 => 10.00 => 72.00
        time_t when = mktime(&date); 
        const struct tm *norm = localtime(&when);
        if (norm->tm_year == y - 1900 && norm->tm_mday == d && norm->tm_mon  == m - 1)
        {
            return (dateString);
        }
    }
    return ;
}

