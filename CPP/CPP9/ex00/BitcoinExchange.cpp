#include "BitcoinExchange.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cctype>
#include <cstdlib>

// ---------------------------------------------------------------------------
// Helpers internes au fichier (invisibles depuis l'extérieur grâce au
// namespace anonyme). Ça évite de polluer l'interface de la classe.
// ---------------------------------------------------------------------------
namespace
{
	std::string trim(const std::string& s)
	{
		std::string::size_type start = s.find_first_not_of(" \t\r\n");
		if (start == std::string::npos)
			return "";
		std::string::size_type end = s.find_last_not_of(" \t\r\n");
		return s.substr(start, end - start + 1);
	}

	bool isLeapYear(int y)
	{
		return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
	}

	// Vérifie le format YYYY-MM-DD ET que la date est cohérente
	// (mois 1-12, jour valide selon le mois, années bissextiles).
	bool isValidDate(const std::string& date)
	{
		if (date.size() != 10)
			return false;
		if (date[4] != '-' || date[7] != '-')
			return false;
		for (std::string::size_type i = 0; i < date.size(); ++i)
		{
			if (i == 4 || i == 7)
				continue;
			if (!std::isdigit(static_cast<unsigned char>(date[i])))
				return false;
		}
		int year  = std::atoi(date.substr(0, 4).c_str());
		int month = std::atoi(date.substr(5, 2).c_str());
		int day   = std::atoi(date.substr(8, 2).c_str());
		if (month < 1 || month > 12 || day < 1)
			return false;
		int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
		int maxDay = daysInMonth[month - 1];
		if (month == 2 && isLeapYear(year))
			maxDay = 29;
		return day <= maxDay;
	}

	// Un nombre = chiffres, un signe optionnel, au plus un point.
	// On garde le signe pour pouvoir détecter les négatifs plus tard.
	bool isNumericFormat(const std::string& s)
	{
		if (s.empty())
			return false;
		std::string::size_type i = 0;
		if (s[i] == '+' || s[i] == '-')
			++i;
		bool hasDigit = false;
		bool hasDot = false;
		for (; i < s.size(); ++i)
		{
			if (s[i] == '.')
			{
				if (hasDot)
					return false;
				hasDot = true;
			}
			else if (std::isdigit(static_cast<unsigned char>(s[i])))
				hasDigit = true;
			else
				return false;
		}
		return hasDigit;
	}
}

// ---------------------------------------------------------------------------
// Forme canonique orthodoxe
// ---------------------------------------------------------------------------
BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
	: _database(other._database) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
		_database = other._database;
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

// ---------------------------------------------------------------------------
// Chargement de la base data.csv (format: "date,exchange_rate")
// ---------------------------------------------------------------------------
bool BitcoinExchange::loadDatabase(const std::string& filename)
{
	std::ifstream file(filename.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: could not open database." << std::endl;
		return false;
	}

	std::string line;
	std::getline(file, line); // saute l'entête "date,exchange_rate"
	while (std::getline(file, line))
	{
		if (line.empty())
			continue;
		std::string::size_type comma = line.find(',');
		if (comma == std::string::npos)
			continue;
		std::string date = trim(line.substr(0, comma));
		std::string rate = trim(line.substr(comma + 1));
		_database[date] = static_cast<float>(std::atof(rate.c_str()));
	}
	return !_database.empty();
}

// ---------------------------------------------------------------------------
// Retrouve le taux. Date exacte si présente, sinon la plus proche inférieure.
// ---------------------------------------------------------------------------
float BitcoinExchange::getRate(const std::string& date) const
{
	// lower_bound = premier élément dont la clé est >= date.
	std::map<std::string, float>::const_iterator it =
		_database.lower_bound(date);

	// Correspondance exacte trouvée.
	if (it != _database.end() && it->first == date)
		return it->second;

	// Pas d'exact : on veut la date juste avant.
	if (it == _database.begin())
		return 0.0f; // aucune date antérieure dans la base
	--it;
	return it->second;
}

// ---------------------------------------------------------------------------
// Traitement du fichier d'entrée (format: "date | value")
// ---------------------------------------------------------------------------
void BitcoinExchange::processInput(const std::string& filename) const
{
	std::ifstream file(filename.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return;
	}

	std::string line;
	std::getline(file, line); // saute l'entête "date | value"
	while (std::getline(file, line))
	{
		if (trim(line).empty())
			continue;

		std::string::size_type pipe = line.find('|');
		if (pipe == std::string::npos)
		{
			std::cerr << "Error: bad input => " << trim(line) << std::endl;
			continue;
		}

		std::string date = trim(line.substr(0, pipe));
		std::string valueStr = trim(line.substr(pipe + 1));

		if (!isValidDate(date))
		{
			std::cerr << "Error: bad input => " << date << std::endl;
			continue;
		}
		if (!isNumericFormat(valueStr))
		{
			std::cerr << "Error: bad input => " << valueStr << std::endl;
			continue;
		}

		double value = std::atof(valueStr.c_str());
		if (value < 0)
		{
			std::cerr << "Error: not a positive number." << std::endl;
			continue;
		}
		if (value > 1000)
		{
			std::cerr << "Error: too large a number." << std::endl;
			continue;
		}

		float rate = getRate(date);
		std::cout << date << " => " << value << " = "
				  << (value * rate) << std::endl;
	}
}