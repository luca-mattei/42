#include "PmergeMe.hpp"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <climits>
#include <sys/time.h>

// ===========================================================================
// Forme canonique orthodoxe
// ===========================================================================
PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other) : _vec(other._vec), _deq(other._deq) {}

PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
	if (this != &other)
	{
		_vec = other._vec;
		_deq = other._deq;
	}
	return *this;
}

PmergeMe::~PmergeMe() {}

// ===========================================================================
// Parsing / validation
// ===========================================================================
static bool parseOne(const std::string& token, int& out)
{
	if (token.empty())
		return false;
	for (std::string::size_type i = 0; i < token.size(); ++i)
	{
		if (token[i] < '0' || token[i] > '9') // pas de signe -> positifs only
			return false;
	}
	char* end = 0;
	long value = std::strtol(token.c_str(), &end, 10);
	if (*end != '\0' || value < 0 || value > INT_MAX)
		return false;
	out = static_cast<int>(value);
	return true;
}

bool PmergeMe::parse(int argc, char** argv)
{
	if (argc < 2)
		return false;
	for (int i = 1; i < argc; ++i)
	{
		int value;
		if (!parseOne(argv[i], value))
			return false;
		_vec.push_back(value);
		_deq.push_back(value);
	}
	return true;
}

// ===========================================================================
// Suite de Jacobsthal : J(0)=0, J(1)=1, J(k)=J(k-1)+2*J(k-2)
// On génère l'ordre d'insertion des "pending" b2..bm :
//   3,2 | 5,4 | 11,10,9,8,7,6 | ...   (bornes de Jacobsthal, ordre décroissant)
// Cet ordre garantit qu'à chaque insertion la plage de recherche a une taille
// de la forme 2^k - 1 -> nombre de comparaisons minimal.
// ===========================================================================
std::vector<size_t> PmergeMe::jacobsthalOrder(size_t nbPairs) const
{
	std::vector<size_t> order;
	if (nbPairs < 2)
		return order;

	size_t prevJ = 1; // J(2)
	size_t a = 1;     // J(k-2)
	size_t b = 1;     // J(k-1)  -> on part de k=3
	while (true)
	{
		size_t curJ = b + 2 * a; // J(k)
		size_t start = (curJ < nbPairs) ? curJ : nbPairs;
		if (start >= prevJ + 1)
		{
			for (size_t idx = start; idx >= prevJ + 1; --idx)
			{
				order.push_back(idx);
				if (idx == prevJ + 1)
					break; // évite l'underflow de size_t
			}
		}
		if (curJ >= nbPairs)
			break;
		prevJ = curJ;
		a = b;
		b = curJ;
	}
	return order;
}

// ===========================================================================
// std::vector : insertion binaire dans chain[0..hi)
// ===========================================================================
int PmergeMe::binaryInsertVector(std::vector<int>& chain, int value, int hi)
{
	int lo = 0;
	while (lo < hi)
	{
		int mid = (lo + hi) / 2;
		if (chain[mid] < value)
			lo = mid + 1;
		else
			hi = mid;
	}
	chain.insert(chain.begin() + lo, value);
	return lo; // position réelle d'insertion
}

void PmergeMe::mergeInsertVector(std::vector<int>& v)
{
	size_t n = v.size();
	if (n < 2)
		return;

	// 1. Straggler (élément seul si n impair)
	bool hasStraggler = (n % 2 == 1);
	int straggler = hasStraggler ? v[n - 1] : 0;

	// 2. Paires (larger, smaller)
	std::vector<std::pair<int, int> > pairs;
	for (size_t i = 0; i + 1 < n; i += 2)
	{
		int x = v[i];
		int y = v[i + 1];
		if (x < y)
			std::swap(x, y);
		pairs.push_back(std::make_pair(x, y)); // first = grand, second = petit
	}

	// 3. Trier récursivement les "grands" (merge-insert sur les larger)
	std::vector<int> largers;
	for (size_t i = 0; i < pairs.size(); ++i)
		largers.push_back(pairs[i].first);
	mergeInsertVector(largers);

	// 4. Réordonner les paires selon les grands triés (gestion des doublons)
	std::vector<bool> used(pairs.size(), false);
	std::vector<std::pair<int, int> > sortedPairs;
	for (size_t i = 0; i < largers.size(); ++i)
	{
		for (size_t j = 0; j < pairs.size(); ++j)
		{
			if (!used[j] && pairs[j].first == largers[i])
			{
				sortedPairs.push_back(pairs[j]);
				used[j] = true;
				break;
			}
		}
	}

	// 5. Chaîne principale = [b0, a0, a1, ..., a(m-1)] ; pending = b1..b(m-1)
	std::vector<int> chain;
	chain.push_back(sortedPairs[0].second);
	std::vector<int> posOfA(sortedPairs.size());
	for (size_t i = 0; i < sortedPairs.size(); ++i)
	{
		chain.push_back(sortedPairs[i].first);
		posOfA[i] = static_cast<int>(i) + 1; // a_i est à l'index i+1
	}

	// 6. Insertion des pending dans l'ordre de Jacobsthal
	std::vector<size_t> order = jacobsthalOrder(sortedPairs.size());
	for (size_t k = 0; k < order.size(); ++k)
	{
		size_t idx = order[k];            // i dans [2..m]
		size_t j = idx - 1;               // paire concernée (0-based)
		int value = sortedPairs[j].second;
		int hi = posOfA[j];               // borne haute = position de son grand
		int insertPos = binaryInsertVector(chain, value, hi);
		// tout grand situé à un index >= insertPos décale d'un cran
		for (size_t t = 0; t < posOfA.size(); ++t)
			if (posOfA[t] >= insertPos)
				++posOfA[t];
	}

	// 7. Straggler par insertion binaire sur toute la chaîne
	if (hasStraggler)
		binaryInsertVector(chain, straggler, static_cast<int>(chain.size()));

	v = chain;
}

// ===========================================================================
// std::deque : mêmes étapes, conteneur différent (pas de fonction générique)
// ===========================================================================
int PmergeMe::binaryInsertDeque(std::deque<int>& chain, int value, int hi)
{
	int lo = 0;
	while (lo < hi)
	{
		int mid = (lo + hi) / 2;
		if (chain[mid] < value)
			lo = mid + 1;
		else
			hi = mid;
	}
	chain.insert(chain.begin() + lo, value);
	return lo;
}

void PmergeMe::mergeInsertDeque(std::deque<int>& d)
{
	size_t n = d.size();
	if (n < 2)
		return;

	bool hasStraggler = (n % 2 == 1);
	int straggler = hasStraggler ? d[n - 1] : 0;

	std::deque<std::pair<int, int> > pairs;
	for (size_t i = 0; i + 1 < n; i += 2)
	{
		int x = d[i];
		int y = d[i + 1];
		if (x < y)
			std::swap(x, y);
		pairs.push_back(std::make_pair(x, y));
	}

	std::deque<int> largers;
	for (size_t i = 0; i < pairs.size(); ++i)
		largers.push_back(pairs[i].first);
	mergeInsertDeque(largers);

	std::deque<bool> used(pairs.size(), false);
	std::deque<std::pair<int, int> > sortedPairs;
	for (size_t i = 0; i < largers.size(); ++i)
	{
		for (size_t j = 0; j < pairs.size(); ++j)
		{
			if (!used[j] && pairs[j].first == largers[i])
			{
				sortedPairs.push_back(pairs[j]);
				used[j] = true;
				break;
			}
		}
	}

	std::deque<int> chain;
	chain.push_back(sortedPairs[0].second);
	std::deque<int> posOfA(sortedPairs.size());
	for (size_t i = 0; i < sortedPairs.size(); ++i)
	{
		chain.push_back(sortedPairs[i].first);
		posOfA[i] = static_cast<int>(i) + 1;
	}

	std::vector<size_t> order = jacobsthalOrder(sortedPairs.size());
	for (size_t k = 0; k < order.size(); ++k)
	{
		size_t idx = order[k];
		size_t j = idx - 1;
		int value = sortedPairs[j].second;
		int hi = posOfA[j];
		int insertPos = binaryInsertDeque(chain, value, hi);
		for (size_t t = 0; t < posOfA.size(); ++t)
			if (posOfA[t] >= insertPos)
				++posOfA[t];
	}

	if (hasStraggler)
		binaryInsertDeque(chain, straggler, static_cast<int>(chain.size()));

	d = chain;
}

// ===========================================================================
// Orchestration + mesure du temps
// ===========================================================================
static double nowMicroseconds()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return static_cast<double>(tv.tv_sec) * 1000000.0
		 + static_cast<double>(tv.tv_usec);
}

void PmergeMe::sortAndReport()
{
	std::cout << "Before:";
	for (size_t i = 0; i < _vec.size(); ++i)
		std::cout << " " << _vec[i];
	std::cout << std::endl;

	double startVec = nowMicroseconds();
	mergeInsertVector(_vec);
	double endVec = nowMicroseconds();

	double startDeq = nowMicroseconds();
	mergeInsertDeque(_deq);
	double endDeq = nowMicroseconds();

	std::cout << "After:";
	for (size_t i = 0; i < _vec.size(); ++i)
		std::cout << " " << _vec[i];
	std::cout << std::endl;

	std::cout << "Time to process a range of " << _vec.size()
			  << " elements with std::vector : "
			  << (endVec - startVec) << " us" << std::endl;
	std::cout << "Time to process a range of " << _deq.size()
			  << " elements with std::deque  : "
			  << (endDeq - startDeq) << " us" << std::endl;
}