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



void    BitcoinExchange::setupDb(std::string &database)
{
    std::string             line;
    std::istringstream      iss(line);
    std::string             dateString;
    Optional<std::string>   actualDate;
    std::string             amountString;
    Optional<float>         actualAmount;
    char                    seperator;

    int i = 0;

    std::ifstream   infile(database.c_str());
    if (!infile.is_open())
        throw std::runtime_error("Cannot open database");
    
    std::getline(infile, line);
    if (line != "date,exchange_rate")
    {
        infile.close();
        throw std::runtime_error("Database format is incorrect");
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

        actualDate = checkInputDate(dateString);
        if (!actualDate.hasValue())
        {
            std::cerr << "Database Error: Line "<< i <<" has a bad date => : " << dateString << std::endl;
            continue ;
        }

        actualAmount = checkInputAmount(amountString);
        if (!actualDate.hasValue())
        {
            continue ;
        }
        _database.insert(std::make_pair(actualDate, actualAmount));        
    }

    infile.close();

    if (_database.size() == 0)
        throw std::runtime_error("Cannot open database");
}

void BitcoinExchange::openUserFile(std::string &userFile)
{
    std::string             line;
    std::istringstream      iss(line);
    std::string             dateString;
    std::string             amountString;
    Optional<std::string>   optionalDate;
    Optional<float>         optionalAmount;
    char                    seperator;
    float                   printRate;

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
        if (!(iss >> dateString >> seperator >> amountString) || seperator != '|')
        {
            std::cerr << "Error: User input line "<< i <<" has bad input => : " << line << std::endl;
            continue ;
        }

        optionalDate = checkInputDate(dateString);
        if (!optionalDate.hasValue())
        {
            std::cerr << "Error: User input line "<< i <<" has a bad date => : " << dateString << std::endl;
            continue ;
        }

        optionalAmount = checkInputAmount(amountString);
        if (!optionalAmount.hasValue())
        {
            continue ;
        }
        printRate = getRateForDate(optionalDate.getValue());
        std::cout << optionalDate.getValue() << " => " << optionalAmount.getValue() << " => " << printRate * optionalAmount.getValue() << std::fixed << std::setprecision(2) << std::endl;
    }
    infile.close();
    return ;
}

float	BitcoinExchange::getRateForDate(std::string date) const
{
    std::map<std::string, float>::const_iterator it = _database.find(date);
    if (it != _database.end())
        return (it->second);
    it = _database.lower_bound(date);
    if (it == _database.begin())
        return (0.0);
    // if iterator is at the end, then lower bound is one less. 
    // or if iterator date is sooner than wanted date, the lower bound is one less. 
    if (it == _database.end() || it->first > date)
        it--;
    return (it->second);
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

