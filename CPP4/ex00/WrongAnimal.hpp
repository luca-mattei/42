#ifndef WRONGANIMAL
#define WRONGANIMAL

#include <string>
#include <iostream>

class WrongAnimal {
protected:
    std::string _type;
public:
    WrongAnimal();
    WrongAnimal(const std::string& type);
    WrongAnimal(const WrongAnimal& other);
	WrongAnimal& operator=(const WrongAnimal& other);
	virtual ~WrongAnimal();

    virtual void makeSound() const;
    std::string getType() const;
};

#endif