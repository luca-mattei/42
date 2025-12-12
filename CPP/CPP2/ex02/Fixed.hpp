#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>

class Fixed
{
private:
    int                 _rawBits;
    static const int    _fractionalBits = 8;

public:
    // Constructeurs et destructeur (Orthodox Canonical Form)
    Fixed(void);
    Fixed(const int n);
    Fixed(const float n);
    Fixed(const Fixed& other);
    Fixed& operator=(const Fixed& other);
    ~Fixed(void);

    // Getters/Setters
    int     getRawBits(void) const;
    void    setRawBits(int const raw);

    // Conversions
    float   toFloat(void) const;
    int     toInt(void) const;

    // Opérateurs de comparaison
    bool    operator>(const Fixed& other) const;
    bool    operator<(const Fixed& other) const;
    bool    operator>=(const Fixed& other) const;
    bool    operator<=(const Fixed& other) const;
    bool    operator==(const Fixed& other) const;
    bool    operator!=(const Fixed& other) const;

    // Opérateurs arithmétiques
    Fixed   operator+(const Fixed& other) const;
    Fixed   operator-(const Fixed& other) const;
    Fixed   operator*(const Fixed& other) const;
    Fixed   operator/(const Fixed& other) const;

    // Opérateurs d'incrémentation/décrémentation
    Fixed&  operator++(void);       // Pré-incrémentation: ++a
    Fixed   operator++(int);        // Post-incrémentation: a++
    Fixed&  operator--(void);       // Pré-décrémentation: --a
    Fixed   operator--(int);        // Post-décrémentation: a--

    // Fonctions statiques min/max
    static Fixed&       min(Fixed& a, Fixed& b);
    static const Fixed& min(const Fixed& a, const Fixed& b);
    static Fixed&       max(Fixed& a, Fixed& b);
    static const Fixed& max(const Fixed& a, const Fixed& b);
};

// Surcharge de l'opérateur 
std::ostream& operator<<(std::ostream& out, const Fixed& fixed);

#endif