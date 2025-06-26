#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <cstring>
#include <exception>

class RPNclass
{
	private:
						RPNclass();
						RPNclass(const RPNclass& copy);
		RPNclass&		operator=(const RPNclass& other);
						~RPNclass();

	public:
		static void		calculate(std::string RPNstr);

};

#endif