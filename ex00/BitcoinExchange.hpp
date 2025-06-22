#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>


class BtcExchange
{
	private:
		std::map<std::string,double> rates;

	public:
						BtcExchange();
						~BtcExchange();
						BtcExchange(const BtcExchange& copy);
		BtcExchange&	operator=(const BtcExchange& copy);

		void			parseBtc(const std::string& gotInp);
		void			computeLine(std::string& date, double amount) const;

};

#endif