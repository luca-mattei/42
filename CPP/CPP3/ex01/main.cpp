#include "ScavTrap.hpp"
#include "../ex00/ClapTrap.hpp"


//takeDamage et beRepaired c'est affiche ClapTrap car ils herite de lui sans override
//attack c'est ecrit trav car override on a changer la stat de base
//guardGate unique a scav 

int main() {

    ScavTrap OG;
	ScavTrap scav = OG;
	std::cout << "--STATS--" << std::endl;
	std::cout << "Named : " << scav.getName() << std::endl;
	std::cout << "HP : " << scav.getHitPoints() << std::endl;
	std::cout << "Energy : " << scav.getEnergyPoints() << std::endl;
	std::cout << "Attack Power : " << scav.getAttackDamage() << std::endl;
	std::cout << "--ACTIONS--" << std::endl;
	scav.attack("target");
	scav.takeDamage(50);
	scav.beRepaired(30);
    scav.guardGate();
	std::cout << "--Destructions--" << std::endl;
    return 0;
}