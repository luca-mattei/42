#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <string>
#include <map>

class BitcoinExchange
{
	private:
		// Clé = date "YYYY-MM-DD", valeur = taux de change.
		// std::map garde les clés triées automatiquement -> pratique pour
		// retrouver la date <= à celle demandée avec lower_bound.
		std::map<std::string, float> _database;

		// Renvoie le taux à appliquer pour une date donnée.
		// Si la date exacte n'existe pas -> date la plus proche INFÉRIEURE.
		float getRate(const std::string& date) const;

	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);
		~BitcoinExchange();

		// Charge data.csv dans la map. false si le fichier est illisible.
		bool loadDatabase(const std::string& filename);

		// Lit le fichier d'entrée ligne par ligne et affiche les résultats.
		void processInput(const std::string& filename) const;
};

#endif