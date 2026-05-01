#include "FragTrap.hpp"

FragTrap::FragTrap() : ClapTrap() {
	_hitPoints = 100;
    _energyPoints = 100;
    _attackDamage = 30;
    std::cout << "FragTrap default constructor called" << std::endl;
}

FragTrap::FragTrap(const std::string& name) : ClapTrap(name) {
	_hitPoints = 100;
    _energyPoints = 100;
    _attackDamage = 30;
    std::cout << "FragTrap" << _name << "constructor called" << std::endl;
}







void FragTrap::highFivesGuys(void) {
	std::cout << "a positive high-fives request" << std::endl;
}