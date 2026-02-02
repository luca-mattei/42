#include "ClapTrap.hpp"

int main(void)
{
	ClapTrap Clap1("ClapClap");
	std::cout << "--STATS--" << std::endl;
	std::cout << "Named : " << Clap1.getName() << std::endl;
	std::cout << "HP : " << Clap1.getHitPoints() << std::endl;
	std::cout << "Energy : " << Clap1.getEnergyPoints() << std::endl;
	std::cout << "Attack Power : " << Clap1.getAttackDamage() << std::endl;
	std::cout << "--ACTIONS--" << std::endl;
	Clap1.attack("target");
	Clap1.takeDamage(5);
	Clap1.beRepaired(3);
	std::cout << "--ENDSTATS--" << std::endl;
	std::cout << "HP after taking 5dmg and repair 3dmg: " << Clap1.getHitPoints() << std::endl;
	std::cout << "Energy after this 2 actions: " << Clap1.getEnergyPoints() << std::endl;
	return (0);
}