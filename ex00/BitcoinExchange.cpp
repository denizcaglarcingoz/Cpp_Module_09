#include "BitcoinExchange.hpp"
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <cstdlib>

static void trim(std::string &s)
{
    size_t p = s.find_first_not_of(" \t");  //continuees until first char other than /t or " " and returns the index of first non space
    if (p == std::string::npos)				//if no posistion found means std::string::npos
	{
		s.clear();
		return;
	}
    s = s.substr(p);
    p = s.find_last_not_of(" \t");			// reverse of first not of
    if (p != std::string::npos)
	{
		s.resize(p+1);
	}
}

BtcExchange::BtcExchange()
{
    std::ifstream data("data.csv");
    if (!data.is_open())
        throw std::runtime_error("Failed to open data.csv");

    std::string line;
    std::getline(data, line);                    // skipping header text

    while (std::getline(data, line))
    {
        std::stringstream ss(line);
        std::string date;
		std::string rateStr;

        if (!std::getline(ss, date, ',') || !std::getline(ss, rateStr))
            throw std::runtime_error("Bad CSV format");

        trim(date);
        trim(rateStr);

        double rate = std::atof(rateStr.c_str());
        rates[date] = rate;                       // insert into map
		//std::cout << "The line " << date << " "<< rate << std::endl;
	}
}

void	BtcExchange::parseBtc(const std::string& gotInp)
{
	std::stringstream ss(gotInp);
	std::string date, value;

	if (!std::getline(ss, date, '|') || !std::getline(ss, value))
	{
		throw std::runtime_error(std::string(("Bad input => ") + gotInp));
	}
	trim(date);
	trim(value);

	double amount = std::atof(value.c_str());

	if (amount < 0)
	{
		throw std::runtime_error("not a positive number.");
	}
	if (amount > 1000)
	{
		throw std::runtime_error("too large a number.");
	}
	computeLine(date, amount);
}

// void BtcExchange::computeLine(std::string& date, double amount) const
// {

// 	for (std::map<std::string,double>::const_iterator it = rates.begin(); it != rates.end(); it++)
// 	{
// 		if (date == it->first)
// 		{
// 			std::cout << date << " => " << amount << " = " << amount * it->second <<std::endl;
// 		}
// 	}


// }

static bool validDate(const std::string& d)
{
    if (d.size() != 10 || d[4] != '-' || d[7] != '-') 
        return false;

    int y   = std::atoi(d.substr(0,4).c_str());
    int m   = std::atoi(d.substr(5,2).c_str());
    int day = std::atoi(d.substr(8,2).c_str());

    if (y < 2000 || y > 2025)
        return false;
    if (m < 1 || m > 12)
        return false;
    if (day < 1 || day > 31)
        return false;

    return true;
}

void BtcExchange::computeLine(std::string& date, double amount) const
{
	if (!validDate(date))
    	throw std::runtime_error("Bad input date");

    if (rates.empty())
        throw std::runtime_error("No rate data");

    // finds first element ≥ date // checks with ascii style like a is 97 > A 65
    std::map<std::string,double>::const_iterator it = rates.lower_bound(date);

    if (it == rates.end())
    {
        // this means it passed all so we have to come back one
        --it;
    }
    else if (it->first != date) // there was no exact date match so we have to go back.
    {
        
        if (it == rates.begin()) // if it is already at the start we can't go backkkkkkkkk
            throw std::runtime_error("No earlier rate available"); 
        --it;  // step back to closest earlier date
    }

    double rate = it->second;

    std::cout
        << date
        << " => "
        << amount
        << " = "
        << (amount * rate)
        << std::endl;
}

BtcExchange::~BtcExchange(){}