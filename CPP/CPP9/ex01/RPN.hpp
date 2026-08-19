#ifndef RPN_HPP
#define RPN_HPP

#include <string>
#include <stack>

class RPN
{
	private:
		// La pile est le cœur de l'algo : on empile les opérandes, et à
		// chaque opérateur on dépile deux valeurs pour les combiner.
		std::stack<int> _stack;

		bool isOperator(char c) const;
		int  applyOperator(int a, int b, char op) const;

	public:
		RPN();
		RPN(const RPN& other);
		RPN& operator=(const RPN& other);
		~RPN();

		// Évalue une expression postfixée. Lance une exception en cas
		// d'erreur (token invalide, pile mal formée, division par zéro).
		int evaluate(const std::string& expression);
};

#endif