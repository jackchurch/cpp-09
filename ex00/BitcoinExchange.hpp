#pragma once

#include <iostream>
#include <fstream>
#include <istream>
#include <map>
#include "Optional.hpp"
#include <sstream>

class BitcoinExchange
{
	private:
		std::map<std::string, float> _database;
	public:
        // Orthodox Canonical
		BitcoinExchange();
		BitcoinExchange(BitcoinExchange const & orignal);
		BitcoinExchange &operator=(BitcoinExchange const & orignal);
		~BitcoinExchange();
		Optional<std::string> data;
		
		void					setupDb(std::string& database);
		void					openUserFile(std::string& userFile);
		float					getRateForDate(std::string date) const;
		Optional<float> 		checkInputAmount(std::string String);
		Optional<std::string> 	checkInputDate(std::string dateString);
	};