#include "FragTrap.hpp"
#include "ClapTrap.hpp"



int main() {

    FragTrap frag("Frag");
	std::cout << "--STATS--" << std::endl;
	std::cout << "Named : " << frag.getName() << std::endl;
	std::cout << "HP : " << frag.getHitPoints() << std::endl;
	std::cout << "Energy : " << frag.getEnergyPoints() << std::endl;
	std::cout << "Attack Power : " << frag.getAttackDamage() << std::endl;
	std::cout << "--ACTIONS--" << std::endl;
	frag.attack("target");
	frag.takeDamage(100);
	frag.beRepaired(30);
    frag.highFivesGuys();
	std::cout << "--Destructions--" << std::endl;
    return 0;
}