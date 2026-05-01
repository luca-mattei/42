#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <cstdlib>

int main() {
    std::srand(42);  // seed fixe pour reproduire les résultats

    // Test 1 : ShrubberyCreationForm
    std::cout << "=== Shrubbery ===" << std::endl;
    try {
        Bureaucrat b("Alice", 136);
        ShrubberyCreationForm f("home");
        b.signForm(f);
        b.executeForm(f);  // crée home_shrubbery
    }
    catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    // Test 2 : RobotomyRequestForm
    std::cout << "\n=== Robotomy ===" << std::endl;
    try {
        Bureaucrat b("Bob", 45);
        RobotomyRequestForm f("Bender");
        b.signForm(f);
        b.executeForm(f);
        b.executeForm(f);  // 2 fois pour voir le 50%
        b.executeForm(f);
    }
    catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    // Test 3 : PresidentialPardonForm
    std::cout << "\n=== Presidential Pardon ===" << std::endl;
    try {
        Bureaucrat b("Charlie", 5);
        PresidentialPardonForm f("Marvin");
        b.signForm(f);
        b.executeForm(f);
    }
    catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    // Test 4 : exécuter sans avoir signé
    std::cout << "\n=== Execute sans signer ===" << std::endl;
    try {
        Bureaucrat b("Dave", 1);
        ShrubberyCreationForm f("garden");
        b.executeForm(f);  // pas signé → erreur
    }
    catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    // Test 5 : grade insuffisant pour exécuter
    std::cout << "\n=== Grade insuffisant pour executer ===" << std::endl;
    try {
        Bureaucrat signer("Signer", 5);
        Bureaucrat executor("Executor", 138);
        ShrubberyCreationForm f("park");
        signer.signForm(f);
        executor.executeForm(f);  // grade 138 > 137 requis → erreur
    }
    catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    return 0;
}