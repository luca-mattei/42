#include "Weapon.hpp"

Weapon::Weapon(const std::string& type) : _type(type) {}

Weapon::~Weapon() {}

void Weapon::setType(const std::string& type) {
	_type = type;
}

const std::string& Weapon::getType(void) {
	return _type;
}
