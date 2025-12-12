#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>

class Fixed
{
	private:
		int                 _rawBits;
		static const int    _fractionalBits = 8;

	public:
		Fixed(void);
		Fixed(const Fixed& other);
		Fixed& operator=(const Fixed& other);
		~Fixed(void);
		
		int     getRawBits(void) const;
		void    setRawBits(int const raw);
};

#endif