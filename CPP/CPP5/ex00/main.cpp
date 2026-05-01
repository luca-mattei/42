#include "Bureaucrat.hpp"

int main() {
    std::cout << "=== Test creation valide ===" << std::endl;
    try {
        Bureaucrat b("Alice", 42);
        std::cout << b << std::endl;
    }
    catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n=== Test grade trop haut ===" << std::endl;
    try {
        Bureaucrat b("Bob", 0);
        std::cout << b << std::endl;
    }
    catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n=== Test grade trop bas ===" << std::endl;
    try {
        Bureaucrat b("Charlie", 151);
        std::cout << b << std::endl;
    }
    catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n=== Test increment au max ===" << std::endl;
    try {
        Bureaucrat b("Dave", 2);
        std::cout << b << std::endl;
        b.incrementGrade();
        std::cout << b << std::endl;  
        b.incrementGrade();           
        std::cout << b << std::endl;
    }
    catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n=== Test decrement au min ===" << std::endl;
    try {
        Bureaucrat b("Eve", 149);
        std::cout << b << std::endl;
        b.decrementGrade();
        std::cout << b << std::endl;
        b.decrementGrade();
        std::cout << b << std::endl;
    }
    catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n=== Test grades limites valides ===" << std::endl;
    try {
        Bureaucrat b1("Min", 1);
        Bureaucrat b2("Max", 150);
        std::cout << b1 << std::endl;
        std::cout << b2 << std::endl;
    }
    catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    return 0;
}