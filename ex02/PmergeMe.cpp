// PmergeMe.cpp
#include "PmergeMe.hpp"
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <utility>
#include <climits>
#include <climits>
#include <cerrno>
#include <cstdlib>

PmergeMe::PmergeMe(int argc, char** argv)
{
    if (argc < 3)
		throw std::invalid_argument("Error: need at least two integer");
    
	for (int i = 1; i < argc; ++i)
	{
		std::string s = argv[i];
		
		//I am finding anything that is not a number or empty
		if (s.empty() || s.find_first_not_of("0123456789") != std::string::npos) 
			throw std::invalid_argument("Error: bad input `" + s + "`");
		
		//I don't accept leading zeros
		if (s.size() > 1 && s[0] == '0')
			throw std::invalid_argument("Error: leading zeeeero");
        
		// I also don't accept overflow and check it here
		errno = 0;
		char* end;
		if (s.size() > 10)
			throw std::out_of_range("Error: integer overflow, please use lower than 2 147 473 647, DTM");
		long val = std::strtol(s.c_str(), &end, 10);
        if (*end != '\0' || errno == ERANGE /*out of range error = ERANGE*/ || val > INT_MAX)
            throw std::out_of_range("Error: integer overflow, please use lower than 2 147 473 647, DTM");

        int x = static_cast<int>(val);
		// push it into both so I can check them both later
        containerVector.push_back(x);
        containerDeque.push_back(x);
    }
}

PmergeMe::PmergeMe(const PmergeMe& copy)
{
	containerVector = copy.containerVector;
	containerDeque = copy.containerDeque;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other)
	{
		containerVector = other.containerVector;
		containerDeque = other.containerDeque;
	}
	return *this;
}

PmergeMe::~PmergeMe()
{}

/// Jacobsthal number insertion
static std::deque<std::size_t> insertionOrderDeq(std::size_t m)   // m = #b-elements
{
	std::deque<std::size_t> ord;
	if (m == 0)
		return ord;

	std::size_t prev_t = 1;          // first block head
	ord.push_back(1);

	// Jacobsthal heads: 1,3,5,11,21,43...
	// My expectatition 1,3,2,5,4,11,10,9,8,7,6,21,20.......,43,42...
	std::size_t j_prevprev = 1;      // J2
	std::size_t j_prev     = 3;      // J3

	while (j_prev <= m)
	{
		std::size_t t = j_prev;      // next head
		ord.push_back(t);
		for (std::size_t i = t - 1; i > prev_t; --i)
		    ord.push_back(i);        // descend until previous head
		prev_t        = t;
		std::size_t j_next = j_prev + 2 * j_prevprev;
		j_prevprev    = j_prev;
		j_prev        = j_next;
	}
	for (std::size_t i = m; i > prev_t; --i)   // tail
		ord.push_back(i);

	return ord;
}

static std::vector<std::size_t> insertionOrderVec(std::size_t m)   // m = #b-elements
{
	std::vector<std::size_t> ord;
	if (m == 0)
		return ord;

	std::size_t prev_t = 1;          // first block head
	ord.push_back(1);

	// Jacobsthal heads: 1,3,5,11,21,43...
	// My expectatition 1,3,2,5,4,11,10,9,8,7,6,21,20.......,43,42...
	std::size_t j_prevprev = 1;      // J2
	std::size_t j_prev     = 3;      // J3

	while (j_prev <= m)
	{
		std::size_t t = j_prev;      // next head
		ord.push_back(t);
		for (std::size_t i = t - 1; i > prev_t; --i)
		    ord.push_back(i);        // descend until previous head
		prev_t        = t;
		std::size_t j_next = j_prev + 2 * j_prevprev;
		j_prevprev    = j_prev;
		j_prev        = j_next;
	}
	for (std::size_t i = m; i > prev_t; --i)   // tail
		ord.push_back(i);

	return ord;
}

void PmergeMe::mergeInsertionSortVector(std::vector<int>& cVector) const
{
    size_t n = cVector.size();
    if (n < 2)
		return;

    std::vector< std::pair<int, int> > pairs; // makin pairs with the next nums, and sorting the pairs while doing it....
    for (size_t i = 0; i + 1 < n; i += 2)
	{
        if (cVector[i] < cVector[i+1])
			pairs.push_back(std::make_pair(cVector[i], cVector[i+1]));
        else
			pairs.push_back(std::make_pair(cVector[i+1], cVector[i]));
    }
    
	bool hasOdd = (n % 2) == 1;  /// NOT FORGETTING THE ODDS AS THEY NEED TO BE PART OF SMALL PART
    int odd = hasOdd ? cVector[n-1] : 0;

   
    std::vector<int> LargeParts; // we add the small parts and odds to this side as it is part of the technqiue
    LargeParts.reserve(pairs.size() + (hasOdd ? 1 : 0));
    for (size_t i = 0; i < pairs.size(); ++i)
	{
        LargeParts.push_back(pairs[i].second);
	}
	if (hasOdd)
		LargeParts.push_back(odd);

    mergeInsertionSortVector(LargeParts); // recursive so I can split more and more pieces small and big groups

    insertVectorSmalls(LargeParts, pairs); //After splitting all, here we add the larger numbers to the sorted smaller parts in recursive returns

    cVector = LargeParts; // finally copy back the sorted value to the referenced container
}

void PmergeMe::insertVectorSmalls(std::vector<int>& largeParts, const std::vector< std::pair<int,int> >& pairs) const
{
	
    // Order must be based on the number of b-elements (=pairs), not on largeParts.
	/// Jacobsthal number insertion
    std::vector<std::size_t> ord = insertionOrderVec(pairs.size());
	
	// std::cout << "Pairs size: "<< pairs.size() << std::endl;
	// std::cout << "Ord size: "<< ord.size() << std::endl;

	// std::cout << "Jacob Sequence-> ";
	// for (size_t i = 0; i < ord.size(); i++)
	// 	std::cout << ord[i] << " ";
	// std::cout << std::endl;

	// if (ord.size() != pairs.size())
	// {
	// 	std::cerr <<"fucking hell" <<std::endl;
	// 	return ;
	// }
    for (std::size_t k = 0; k < pairs.size(); ++k)
    {
        std::size_t idx = ord[k] - 1;  //        // insertionOrder is 1-based so making it 0-based
        int L = pairs[idx].first;

        std::vector<int>::iterator pos = std::upper_bound(largeParts.begin(), largeParts.end(), L);

        largeParts.insert(pos, L);
    }
}

void	PmergeMe::mergeInsertionSortDeque(std::deque<int>& cDeque) const  //THIS ONE IS AS SAME AS VECTOR IN LOGIC
{
	size_t n = cDeque.size();
	if (n <= 1) return;

	std::deque< std::pair<int,int> > pairs;
	for (size_t i = 0; i + 1 < n; i += 2)
	{
		if (cDeque[i] < cDeque[i+1])
			pairs.push_back(std::make_pair(cDeque[i], cDeque[i+1]));
		else
			pairs.push_back(std::make_pair(cDeque[i+1], cDeque[i]));
	}
    
	bool hasOdd = (n % 2) == 1;
	int odd = hasOdd ? cDeque[n-1] : 0;

	std::deque<int> LargeParts;
	for (size_t i = 0; i < pairs.size(); ++i)
		LargeParts.push_back(pairs[i].second);
	
	if (hasOdd)
		LargeParts.push_back(odd);

	mergeInsertionSortDeque(LargeParts);
	insertDequeSmalls(LargeParts, pairs);
	cDeque = LargeParts;
}

void PmergeMe::insertDequeSmalls(std::deque<int>& largeParts, const std::deque<std::pair<int,int> >& pairs) const
{
    // Order must be based on the number of b-elements (=pairs), not on largeParts.
	/// Jacobsthal number insertion
    std::deque<std::size_t> ord = insertionOrderDeq(pairs.size());
	
	// std::cout << "Pairs size: "<< pairs.size() << std::endl;
	// std::cout << "Ord size: "<< ord.size() << std::endl;

	// std::cout << "Jacob Sequence-> ";
	// for (size_t i = 0; i < ord.size(); i++)
	// 	std::cout << ord[i] << " ";
	// std::cout << std::endl;

	// if (ord.size() != pairs.size())
	// {
	// 	std::cerr <<"fucking hell" <<std::endl;
	// 	return ;
	// }
    for (std::size_t k = 0; k < pairs.size(); ++k)
    {
        std::size_t idx = ord[k] - 1;  //        // insertionOrder is 1-based so making it 0-based
        int L = pairs[idx].first;

        std::deque<int>::iterator pos =
            std::upper_bound(largeParts.begin(), largeParts.end(), L);

        largeParts.insert(pos, L);
    }
}

// void PmergeMe::insertDequeSmalls(std::deque<int>& LargeParts, const std::deque< std::pair<int,int> >& pairs) const
// {
//     for (size_t i = 0; i < pairs.size(); ++i)
// 	{
// 		int L = pairs[i].first;
// 		std::deque<int>::iterator pos = std::upper_bound(LargeParts.begin(), LargeParts.end(), L);
// 		LargeParts.insert(pos, L);
//     }
// }

void	PmergeMe::sort()
{
	// Before printings, it includes the same as input
	std::cout << "Before: ";
	for (size_t i = 0; i < containerVector.size(); ++i)
	    std::cout << containerVector[i] << ' ';
    std::cout << '\n';

    // Sort & time vector
    //std::vector<int> tmpVec = containerVector;
	//  std::clock is CPU-time ticks, adding /(double)ClOCKS_PER_SEC * 1e6 turns it into microseconds
    std::clock_t timeStart = std::clock();
    mergeInsertionSortVector(containerVector);
    double durationVec = (std::clock() - timeStart) / (double)CLOCKS_PER_SEC * 1e6;

    // Sort & time deque
    //std::deque<int> tmpDeq = containerDeque;
    timeStart = std::clock();
    mergeInsertionSortDeque(containerDeque);
    double durationDeque = (std::clock() - timeStart) / (double)CLOCKS_PER_SEC * 1e6;

    // After (print sorted vector), it doesn't matter which one I used so I use the Vector.
    std::cout << "After : ";
    for (size_t i = 0; i < containerDeque.size(); ++i)
        std::cout << containerDeque[i] << ' ';
    std::cout << '\n';

    //  Printing timings of Vector and Deque. Vector is faster due to memory contagious style, not blocks of arrray like deqeue
    std::cout
        << "Time to process a range of " << containerVector.size()
        << " elements with std::vector : " << durationVec << " microseconds\n"
        << "Time to process a range of " << containerDeque.size()
        << " elements with std::deque  : " << durationDeque << " microseconds\n";
}