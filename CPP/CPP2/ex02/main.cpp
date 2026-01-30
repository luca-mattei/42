#include <iostream>
#include "Fixed.hpp"

int main()
{
    Fixed a(5.5f);
    Fixed b(2);
    Fixed c = a + b;
    Fixed d = a - b;
    Fixed e = a * b;
    Fixed f = a / b;

    std::cout << "a = " << a << '\n';
    std::cout << "b = " << b << '\n';
    std::cout << "a + b = " << c << '\n';
    std::cout << "a - b = " << d << '\n';
    std::cout << "a * b = " << e << '\n';
    std::cout << "a / b = " << f << '\n';

    std::cout << std::boolalpha;
    std::cout << "a > b: "  << (a > b)  << '\n';
    std::cout << "a < b: "  << (a < b)  << '\n';
    std::cout << "a >= b: " << (a >= b) << '\n';
    std::cout << "a <= b: " << (a <= b) << '\n';
    std::cout << "a == b: " << (a == b) << '\n';
    std::cout << "a != b: " << (a != b) << '\n';

    std::cout << "a as int: " << a.toInt() << '\n';
    std::cout << "b as int: " << b.toInt() << '\n';

    return 0;
}

// #include <iostream>
// #include "Fixed.hpp"
// int main( void ) {
// Fixed a;
// Fixed const b( Fixed( 5.05f ) * Fixed( 2 ) );
// std::cout << a << std::endl;
// std::cout << ++a << std::endl;
// std::cout << a << std::endl;
// std::cout << a++ << std::endl;
// std::cout << a << std::endl;
// std::cout << b << std::endl;
// std::cout << Fixed::max( a, b ) << std::endl;
// return 0;
// }