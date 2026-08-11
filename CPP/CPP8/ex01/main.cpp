#include "Span.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

int main()
{
    //Tests basics
    {
        Span sp = Span(5);
        sp.addNumber(6);
        sp.addNumber(3);
        sp.addNumber(17);
        sp.addNumber(9);
        sp.addNumber(11);
        std::cout << sp.shortestSpan() << std::endl;   // 2
        std::cout << sp.longestSpan() << std::endl;    // 14
    }

	// container plein
    {
        Span sp(2);
        sp.addNumber(1);
        sp.addNumber(2);
        try {
            sp.addNumber(3);
        } catch (std::exception& e) {
            std::cout << "Full: " << e.what() << std::endl;
        }
    }

    // pas assez de nombres
    {
        Span sp(5);
        sp.addNumber(42);
        try {
            sp.shortestSpan();
        } catch (std::exception& e) {
            std::cout << "Too few: " << e.what() << std::endl;
        }
    }

    //Remplissage par range d'iterateurs
    {
        std::vector<int> src;
        src.push_back(20);
        src.push_back(5);
        src.push_back(50);
        Span sp(3);
        sp.addRange(src.begin(), src.end());
        std::cout << "Range shortest: " << sp.shortestSpan() << std::endl; // 15
        std::cout << "Range longest: "  << sp.longestSpan()  << std::endl; // 45
    }

    //Test à grande echelle : 10 000 nombres
    {
        std::srand(std::time(0));
        Span sp(10000);
        std::vector<int> big;
        for (int i = 0; i < 10000; ++i)
            big.push_back(std::rand());
        sp.addRange(big.begin(), big.end());
        std::cout << "Big shortest: " << sp.shortestSpan() << std::endl;
        std::cout << "Big longest: "  << sp.longestSpan()  << std::endl;
    }

    return 0;
}