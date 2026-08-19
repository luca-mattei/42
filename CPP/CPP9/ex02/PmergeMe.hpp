#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <string>

class PmergeMe
{
	private:
		std::vector<int> _vec;
		std::deque<int>  _deq;

		// --- version std::vector ---
		void mergeInsertVector(std::vector<int>& v);
		int  binaryInsertVector(std::vector<int>& chain, int value, int hi);

		// --- version std::deque ---
		void mergeInsertDeque(std::deque<int>& d);
		int  binaryInsertDeque(std::deque<int>& chain, int value, int hi);

		// Ordre d'insertion des "pending" dicté par la suite de Jacobsthal.
		std::vector<size_t> jacobsthalOrder(size_t nbPairs) const;

	public:
		PmergeMe();
		PmergeMe(const PmergeMe& other);
		PmergeMe& operator=(const PmergeMe& other);
		~PmergeMe();

		// Valide et stocke la séquence. false en cas d'entrée invalide.
		bool parse(int argc, char** argv);

		// Trie avec les deux conteneurs, mesure et affiche.
		void sortAndReport();
};

#endif