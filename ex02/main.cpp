// main.cpp
#include "PmergeMe.hpp"
#include <iostream>

int main(int argc, char** argv)
{
	try
	{
	    PmergeMe sortCompare(argc, argv);
	    sortCompare.sort();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return 1;
	}
	return 0;
}