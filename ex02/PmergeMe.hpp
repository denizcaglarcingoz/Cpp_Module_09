// PmergeMe.hpp
#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <utility>
#include <string>

class PmergeMe
{

	private:
		std::vector<int> containerVector;
		std::deque<int>  containerDeque;

		void mergeInsertionSortVector(std::vector<int>& c) const;
		void insertVectorSmalls(std::vector<int>& S, const std::vector< std::pair<int, int> >& pairs) const;

		void mergeInsertionSortDeque(std::deque<int>& c) const;
		void insertDequeSmalls(std::deque<int>& S, const std::deque< std::pair<int, int> >& pairs) const;

	public:
		PmergeMe(int argc, char** argv);
		PmergeMe(const PmergeMe& copy);
		PmergeMe& operator=(const PmergeMe& other);
		~PmergeMe();

		void sort();
};

#endif // PMERGEME_HPP