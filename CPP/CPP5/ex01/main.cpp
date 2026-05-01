#include "Bureaucrat.hpp"
#include "Form.hpp"

int main() {
    std::cout << "=== Test signature réussie ===" << std::endl;
    try {
        Bureaucrat b("Lilia", 10);
		std::cout << b << std::endl;
        Form f("Formulaire A", 50, 25);
        std::cout << f << std::endl;
        b.signForm(f);
        std::cout << f << std::endl;
        b.signForm(f);
        std::cout << f << std::endl;
    }
    catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n=== Test signature echouee ===" << std::endl;
    try {
        Bureaucrat b("Luca", 100);
		std::cout << b << std::endl;
        Form f("Formulaire B", 50, 25);
        std::cout << f << std::endl;
        b.signForm(f);
        std::cout << f << std::endl;
    }
    catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n=== Test form grade invalide ===" << std::endl;
    try {
        Form f("Formulaire C", 0, 25);
    }
    catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    std::cout << "\n=== Test affichage ===" << std::endl;
    try {
        Bureaucrat b("Bureaucrat", 1);
        Form f("Formulaire D", 1, 1);
        std::cout << b << std::endl;
        std::cout << f << std::endl;
        b.signForm(f);
        std::cout << f << std::endl;
    }
    catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    return 0;
}