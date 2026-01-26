#include "ClapTrap.hpp"

int main(void)
{
	ClapTrap player1("player1");
	ClapTrap player2("player2");
	player1.attack("player2");
	player2.takeDamage(5);
	player2.beRepaired(3);
}