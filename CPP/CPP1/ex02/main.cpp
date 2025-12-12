#include <string>
#include <iostream>


int main()
{
	std::string	str = "HI THIS IS BRAIN";
	std::string* stringPTR = NULL;
	std::string& stringREF = str;
	stringPTR = &str;

	std::cout << "OG string memory address: " <<  &str << "\n";
	std::cout << "stringPTR memory address: " <<  stringPTR << "\n";
	std::cout << "stringREF memory address: " <<  &stringREF << "\n";

	std::cout << "OG string value: " <<  str << "\n";
	std::cout << "stringPTR value: " <<  *stringPTR << "\n";
	std::cout << "stringREF value: " <<  stringREF << "\n";
	return (0);
}