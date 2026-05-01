#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "Intern.hpp"
#include <cstdlib>

int main() {
    std::srand(42);
    Intern intern;
    AForm* f;

    // Test 1 : robotomy request
    std::cout << "=== Robotomy ===" << std::endl;
    f = intern.makeForm("robotomy request", "Bender");
    if (f) {
        Bureaucrat b("Bob", 45);
        b.signForm(*f);
        b.executeForm(*f);
        delete f;
    }

    // Test 2 : shrubbery creation
    std::cout << "\n=== Shrubbery ===" << std::endl;
    f = intern.makeForm("shrubbery creation", "home");
    if (f) {
        Bureaucrat b("Alice", 136);
        b.signForm(*f);
        b.executeForm(*f);
        delete f;
    }

    // Test 3 : presidential pardon
    std::cout << "\n=== Pardon ===" << std::endl;
    f = intern.makeForm("presidential pardon", "Marvin");
    if (f) {
        Bureaucrat b("Charlie", 5);
        b.signForm(*f);
        b.executeForm(*f);
        delete f;
    }

    // Test 4 : form inexistant
    std::cout << "\n=== Form inexistant ===" << std::endl;
    f = intern.makeForm("coffee request", "Dave");
    if (f)
        delete f;

    return 0;
}