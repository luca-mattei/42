#include "Base.hpp"

// Crée aléatoirement un A, B ou C et le retourne comme Base*
Base* generate(void) {
    switch (std::rand() % 3) {
        case 0: return new A();
        case 1: return new B();
        default: return new C();
    }
}

// Identification via pointeur — dynamic_cast retourne NULL si échec
void identify(Base* p) {
    if (dynamic_cast<A*>(p))
        std::cout << "A" << std::endl;
    else if (dynamic_cast<B*>(p))
        std::cout << "B" << std::endl;
    else if (dynamic_cast<C*>(p))
        std::cout << "C" << std::endl;
    else
        std::cout << "unknown" << std::endl;
}

// Identification via référence — dynamic_cast throw si échec
// interdiction d'utiliser un pointeur dans cette fonction
void identify(Base& p) {
    try {
        (void)dynamic_cast<A&>(p);
        std::cout << "A" << std::endl;
        return;
    } catch (std::exception&) {}

    try {
        (void)dynamic_cast<B&>(p);
        std::cout << "B" << std::endl;
        return;
    } catch (std::exception&) {}

    std::cout << "C" << std::endl;
}