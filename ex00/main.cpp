#include "BitcoinExchange.hpp"
#include <fstream>


int main (int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << "Please put proper input" << std::endl;
		return 1;
	}

	std::ifstream in(argv[1]);    // open for reading
    if (!in.is_open())
	{
		std::cout << "Failed to open" << std::endl;
		return 1;
	}
	std::cout << "The file is open" << std::endl;
	
	std::string line;
	std::getline(in , line); // passing the intro text

	BtcExchange btc;

	while (std::getline(in, line))
	{
		if (line.empty())
			continue;

		try
		{
			btc.parseBtc(line);
		}
		catch( const std::exception& e)
		{
			std::cerr << "Error: " << e.what() << std::endl;
		}

	}

}