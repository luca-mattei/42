#include "Zombie.hpp"

Zombie::Zombie() : _name("") {}

Zombie::~Zombie() {
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

void Zombie::setName(std::string name) {
	_name = name;
}

