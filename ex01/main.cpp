#include "RPN.hpp"

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

int main(int argc, char **argv)
{
	if (argc != 2)
		return std::cerr << "Please put proper input1" << std::endl, 1;

	int NumOpDiff = 0;
	std::string RPNstr = argv[1];
	trim(RPNstr);
	if (RPNstr.length() %2 != 1)
		return std::cerr << "Please put proper input1" << std::endl, 1;
	for (int i = 0; i < static_cast<int>(RPNstr.length()); ++i)
	{
		char c = RPNstr[i];
		if (std::isdigit(static_cast<unsigned char>(c)))
			++NumOpDiff;
		else if (c=='+'||c=='-'||c=='*'||c=='/')
		{
			if (NumOpDiff < 2)
				return std::cerr << "Please put proper input3\n", 1;
			--NumOpDiff;
		}
		else
			return std::cerr << "Please put proper input4\n", 1;

		if (i != static_cast<int>(RPNstr.length() - 1) && RPNstr[i+1] != ' ' && (i%2 == 1))
			return std::cerr << "Please put proper input5\n", 1;
		else
		{
			i++;
			if (i >= static_cast<int>(RPNstr.length()))
				break ;
		}
	}

	if (NumOpDiff != 1)
		return std::cerr << "Please put proper input6\n", 1;

	try
	{
		RPNclass::calculate(RPNstr);
	}catch (const std::exception& e)
	{
		std::cerr << e.what();
		return 1;
	}
	// RPNclass rpn;
	// rpn.calculate();
	return 0;
	
}