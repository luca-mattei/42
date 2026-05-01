#include "Base.hpp"

int main() {
    std::srand(std::time(NULL));

    for (int i = 0; i < 6; i++) {
        Base* p = generate();

        std::cout << "Via pointeur : ";
        identify(p);

        std::cout << "Via reference: ";
        identify(*p);

        std::cout << std::endl;
        delete p;
    }
    return 0;
}