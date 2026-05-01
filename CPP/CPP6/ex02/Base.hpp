#ifndef BASE_HPP
#define BASE_HPP

#include <iostream>
#include <cstdlib>
#include <ctime>

// Base doit avoir au moins un virtual pour que dynamic_cast fonctionne
class Base {
public:
    virtual ~Base() {}
};

// Classes vides qui héritent de Base
class A : public Base {};
class B : public Base {};
class C : public Base {};

// Fonctions
Base*   generate(void);
void    identify(Base* p);
void    identify(Base& p);

#endif