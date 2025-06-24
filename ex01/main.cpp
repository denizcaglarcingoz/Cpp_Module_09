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
	{
		std::cerr << "Please put proper input1" << std::endl;
		return 1;
	}

	int NumOpDiff = 0;
	std::string RPN = argv[1];
	trim(RPN);
	for (int i = 1; i < RPN.length(); ++i)
	{
		char c = RPN[i];
		if (std::isdigit(static_cast<unsigned char>(c)))
		{
			++NumOpDiff;
		}
		else if (c=='+'||c=='-'||c=='*'||c=='/')
		{
			if (NumOpDiff < 2)
			{
				std::cerr << "Please put proper input3\n";
				return 1;
			}
			--NumOpDiff;
		}
		else
		{
			std::cerr << "Please put proper input4\n";
			return 1;
		}
		if (!(RPN[i+1] == '\0' || RPN[i+1] == ' '))
		{	
			std::cerr << "Please put proper input5\n";
			return 1;
		}
		else
		{
			i++;
		}
	}

	if (NumOpDiff != 1)
		return std::cerr << "Please put proper input6\n", 1;

	return 0;
}