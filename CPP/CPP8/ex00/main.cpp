// main.cpp
#include "easyfind.hpp"
#include <vector>
#include <list>
#include <iostream>

int main()
{
    std::vector<int> vec = {0, 2, 4, 6, 8, 10, 12, 14, 16, 18};

	try {
		std::vector<int>::iterator it = easyfind(vec, 8);
		std::cout << " Value found: " << *it << std::endl;
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

    try {
        easyfind(vec, 42);
    } catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    std::list<int> lst(vec.begin(), vec.end());
    try {
        std::list<int>::iterator it = easyfind(lst, 6);
        std::cout << "Value found " << *it << std::endl;
    } catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    return 0;
}