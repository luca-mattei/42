#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>
#include <cmath>

class Fixed {
private:
    int                 _value;
    static const int    _fractionalBits = 8;

public:
    Fixed();
    Fixed(const int intValue);
    Fixed(const float floatValue);
    Fixed(const Fixed& other);
    
    ~Fixed();
    
    Fixed& operator=(const Fixed& other);
    
    int getRawBits(void) const;
    void setRawBits(int const raw);
    
    float toFloat(void) const;
    int toInt(void) const;
};

std::ostream& operator<<(std::ostream& os, const Fixed& fixed);

#endif