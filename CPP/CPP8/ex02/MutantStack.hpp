#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP

#include <stack>
#include <deque>

template <typename T>
class MutantStack : public std::stack<T>
{
public:
    MutantStack() {}
    MutantStack(const MutantStack& other) : std::stack<T>(other) {}
    MutantStack& operator=(const MutantStack& other)
    {
        std::stack<T>::operator=(other);
        return *this;
    }
    ~MutantStack() {}

    // Le type d'iterateur = celui du container sous-jacent (deque par defaut)
    typedef typename std::stack<T>::container_type::iterator iterator;
    typedef typename std::stack<T>::container_type::const_iterator const_iterator;

    // On expose les iterateurs du container cache "c"
    iterator begin() { return this->c.begin(); }
    iterator end()   { return this->c.end(); }

    const_iterator begin() const { return this->c.begin(); }
    const_iterator end()   const { return this->c.end(); }
};

#endif