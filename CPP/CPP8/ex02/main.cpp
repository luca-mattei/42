#include "MutantStack.hpp"
#include <iostream>
#include <list>

int main()
{
    std::cout << "--- MutantStack ---" << std::endl;
    {
        MutantStack<int> mstack;

        mstack.push(5);
        mstack.push(17);

        std::cout << mstack.top() << std::endl;   // 17

        mstack.pop();

        std::cout << mstack.size() << std::endl;  // 1

        mstack.push(3);
        mstack.push(5);
        mstack.push(737);
        mstack.push(0);

        MutantStack<int>::iterator it = mstack.begin();
        MutantStack<int>::iterator ite = mstack.end();

        ++it;
        --it;
        while (it != ite)
        {
            std::cout << *it << std::endl;
            ++it;
        }
        std::stack<int> s(mstack);   // un MutantStack EST un stack → conversion OK
    }

    // Preuve d'equivalence : meme test avec une std::list → meme sortie
    std::cout << "--- std::list (meme comportement attendu) ---" << std::endl;
    {
        std::list<int> lst;

        lst.push_back(5);
        lst.push_back(17);
        std::cout << lst.back() << std::endl;   // 17 (top → back)
        lst.pop_back();
        std::cout << lst.size() << std::endl;   // 1

        lst.push_back(3);
        lst.push_back(5);
        lst.push_back(737);
        lst.push_back(0);

        std::list<int>::iterator it = lst.begin();
        std::list<int>::iterator ite = lst.end();

        ++it;
        --it;
        while (it != ite)
        {
            std::cout << *it << std::endl;
            ++it;
        }
    }

    return 0;
}