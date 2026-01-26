#include "Fixed.hpp"
#include <cmath>


Fixed::Fixed(void) : _rawBits(0)
{
}

Fixed::Fixed(const int n) : _rawBits(n << _fractionalBits)
{
    // Décalage de n bits vers la gauche pour obtenir la valeur fixe
    // Ex: 42 << 8 = 10752
}

Fixed::Fixed(const float n) : _rawBits(roundf(n * (1 << _fractionalBits)))
{
    // Multiplie par 2^8 (256) et arrondit
    // Ex: 42.42 * 256 = 10859.52 → 10860
}

Fixed::Fixed(const Fixed& other) : _rawBits(other._rawBits)
{
}

Fixed& Fixed::operator=(const Fixed& other)
{
    if (this != &other)
        this->_rawBits = other._rawBits;
    return *this;
}

Fixed::~Fixed(void)
{
}

int Fixed::getRawBits(void) const
{
    return this->_rawBits;
}

void Fixed::setRawBits(int const raw)
{
    this->_rawBits = raw;
}

float Fixed::toFloat(void) const
{
    return (float)this->_rawBits / (1 << _fractionalBits);
}

int Fixed::toInt(void) const
{
    return this->_rawBits >> _fractionalBits;
}


bool Fixed::operator>(const Fixed& other) const
{
    return this->_rawBits > other._rawBits;
}

bool Fixed::operator<(const Fixed& other) const
{
    return this->_rawBits < other._rawBits;
}

bool Fixed::operator>=(const Fixed& other) const
{
    return this->_rawBits >= other._rawBits;
}

bool Fixed::operator<=(const Fixed& other) const
{
    return this->_rawBits <= other._rawBits;
}

bool Fixed::operator==(const Fixed& other) const
{
    return this->_rawBits == other._rawBits;
}

bool Fixed::operator!=(const Fixed& other) const
{
    return this->_rawBits != other._rawBits;
}

Fixed Fixed::operator+(const Fixed& other) const
{
    Fixed result;
    result.setRawBits(this->_rawBits + other._rawBits);
    return result;
}

Fixed Fixed::operator-(const Fixed& other) const
{
    Fixed result;
    result.setRawBits(this->_rawBits - other._rawBits);
    return result;
}

Fixed Fixed::operator*(const Fixed& other) const
{
    Fixed result;
    // Multiplication de deux nombres en virgule fixe
    // Il faut diviser par 2^fractionalBits après la multiplication
    result.setRawBits((this->_rawBits * other._rawBits) >> _fractionalBits);
    return result;
}

Fixed Fixed::operator/(const Fixed& other) const
{
    Fixed result;
    // Division de deux nombres en virgule fixe
    // Il faut multiplier par 2^fractionalBits avant la division
    result.setRawBits((this->_rawBits << _fractionalBits) / other._rawBits);
    return result;
}

Fixed& Fixed::operator++(void)
{
    this->_rawBits++;
    return *this;
}

Fixed Fixed::operator++(int)
{
    Fixed temp(*this);
    this->_rawBits++;
    return temp;
}

Fixed& Fixed::operator--(void)
{
    this->_rawBits--;
    return *this;
}

Fixed Fixed::operator--(int)
{
    Fixed temp(*this);
    this->_rawBits--;
    return temp;
}


Fixed& Fixed::min(Fixed& a, Fixed& b)
{
    return (a < b) ? a : b;
}

const Fixed& Fixed::min(const Fixed& a, const Fixed& b)
{
    return (a < b) ? a : b;
}

Fixed& Fixed::max(Fixed& a, Fixed& b)
{
    return (a > b) ? a : b;
}

const Fixed& Fixed::max(const Fixed& a, const Fixed& b)
{
    return (a > b) ? a : b;
}

std::ostream& operator<<(std::ostream& out, const Fixed& fixed)
{
    out << fixed.toFloat();
    return out;
}