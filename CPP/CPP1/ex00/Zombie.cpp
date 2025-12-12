#include "Zombie.hpp"

Zombie::Zombie(std::string name) : _name(name)
{}

Zombie::~Zombie()
{
    std::cout << _name << " est détruit" << std::endl;
}

void Zombie::announce (void)
{
	if (_name == "Foo")
	{
		std::cout << _name << ": BraiiiiiiinnnzzzZ..." << "\n";
		return;
	}
	std::cout << "<" << _name <<  ">" << ": BraiiiiiiinnnzzzZ..." << "\n";
}


