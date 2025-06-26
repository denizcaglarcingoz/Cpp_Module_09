#include "RPN.hpp"
#include <list>
#include <sstream>


void	RPNclass::calculate(std::string RPNstr)
{
	std::list<int> st;
	std::istringstream ss(RPNstr);
	std::string token;

	while (ss >> token)
	{
		char c = token[0];
		if (std::isdigit(static_cast<unsigned char>(c)))
		{
			st.push_front(c - '0');
		}
		else
		{
			// operator
			if (st.size() < 2)
				throw std::runtime_error("Error\n");
			
			int rhs = st.front(); // It returns the top but doesn't remove so I also need pop
			st.pop_front();
			int lhs = st.front();
			st.pop_front();
			int res;
			switch (c)
			{
				case '+': res = lhs + rhs; break;
				case '-': res = lhs - rhs; break;
				case '*': res = lhs * rhs; break;
				case '/': res = lhs / rhs; break;
			}
			st.push_front(res);
		}
	}
	if (st.size() != 1)
		throw std::runtime_error("Error\n");
	std::cout << st.front() << "\n";

}