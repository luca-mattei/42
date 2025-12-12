#include "Weapon.hpp"
#include "HumanA.hpp"
#include "HumanB.hpp"

int main()
{
	{
		Weapon club = Weapon("Big Meth Cristal");
		
		HumanA bob("Yanis", club);
	  	bob.attack();
	  	club.setType("meth in sereigue");
	  	bob.attack();
  }
  {
		Weapon club = Weapon("big knife");
HumanB jim("Luca");
// jim.setWeapon(club);
jim.attack();
jim.setWeapon(club);
jim.attack();
club.setType("ma bite");
jim.attack();
  }
  return 0; }