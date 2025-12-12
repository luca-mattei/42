#include "Fixed.hpp"


Fixed::Fixed() : _value(0)
{
    std::cout << "Default constructor called" << std::endl;
}
// intValue << _fractionalBits = intValue x 256
Fixed::Fixed(const int intValue)
{
    std::cout << "Int constructor called" << std::endl;
    _value = intValue << _fractionalBits;
}
// _value = roundf(floatValue * (1 << _fractionalBits)) = floatValue x 256
// (decalage bit direct comme pour int impossible car flat par entier)
Fixed::Fixed(const float floatValue) {
    std::cout << "Float constructor called" << std::endl;
    _value = roundf(floatValue * (1 << _fractionalBits));
}

Fixed::Fixed(const Fixed& other) {
    std::cout << "Copy constructor called" << std::endl;
    *this = other;
}

Fixed::~Fixed() {
    std::cout << "Destructor called" << std::endl;
}

Fixed& Fixed::operator=(const Fixed& other) {
    std::cout << "Copy assignment operator called" << std::endl;
    if (this != &other)
	{
        this->_value = other.getRawBits();
    }
    return *this;
}

int Fixed::getRawBits(void) const {
    return _value;
}

void Fixed::setRawBits(int const raw) {
    _value = raw;
}

float Fixed::toFloat(void) const {
    return (float)_value / (1 << _fractionalBits);
}

int Fixed::toInt(void) const {
    return _value >> _fractionalBits;
}

std::ostream& operator<<(std::ostream& os, const Fixed& fixed) {
    os << fixed.toFloat();
    return os;
}