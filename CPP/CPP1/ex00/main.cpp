#include "Zombie.hpp"

int main(void)
{
	Zombie* z1 = newZombie("Trevor");
	Zombie* z2 = newZombie("saucisse");

	z2->announce();
	z1->announce();
	z2->announce();

	delete z1;
	delete z2;

	return 0;
}
