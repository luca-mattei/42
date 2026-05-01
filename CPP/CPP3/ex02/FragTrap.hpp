#ifndef FRAGTRAP_HPP
#define FRAGTRAP_HPP

#include "../ex00/ClapTrap.hpp"

class FragTrap: public ClapTrap {
	public:
		FragTrap();
		FragTrap(const std::string& name);
		FragTrap(const FragTrap& other);
		FragTrap& operator=(const FragTrap& other);
		~FragTrap();
		void highFivesGuys(void);
};
#endif