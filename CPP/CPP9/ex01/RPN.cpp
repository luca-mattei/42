#include "RPN.hpp"
#include <sstream>
#include <stdexcept>
#include <cctype>

// ---------------------------------------------------------------------------
// Forme canonique orthodoxe
// ---------------------------------------------------------------------------
RPN::RPN() {}

RPN::RPN(const RPN& other) : _stack(other._stack) {}

RPN& RPN::operator=(const RPN& other)
{
	if (this != &other)
		_stack = other._stack;
	return *this;
}

RPN::~RPN() {}

// ---------------------------------------------------------------------------
bool RPN::isOperator(char c) const
{
	return c == '+' || c == '-' || c == '*' || c == '/';
}

int RPN::applyOperator(int a, int b, char op) const
{
	switch (op)
	{
		case '+': return a + b;
		case '-': return a - b;
		case '*': return a * b;
		case '/':
			if (b == 0)
				throw std::runtime_error("division by zero");
			return a / b;
	}
	throw std::runtime_error("unknown operator");
}

// ---------------------------------------------------------------------------
// Évaluation : on découpe l'expression par les espaces, puis on traite
// chaque token dans l'ordre (parcours gauche -> droite).
// ---------------------------------------------------------------------------
int RPN::evaluate(const std::string& expression)
{
	// Repart d'une pile vide (au cas où evaluate serait rappelé).
	while (!_stack.empty())
		_stack.pop();

	std::istringstream iss(expression);
	std::string token;

	while (iss >> token)
	{
		// Un opérande valide = exactement un chiffre (nombres < 10).
		if (token.size() == 1 && std::isdigit(static_cast<unsigned char>(token[0])))
		{
			_stack.push(token[0] - '0');
		}
		else if (token.size() == 1 && isOperator(token[0]))
		{
			// Il faut au moins deux opérandes disponibles.
			if (_stack.size() < 2)
				throw std::runtime_error("not enough operands");

			// Attention à l'ordre : le premier dépilé est l'opérande DROITE.
			int b = _stack.top(); _stack.pop();
			int a = _stack.top(); _stack.pop();
			_stack.push(applyOperator(a, b, token[0]));
		}
		else
		{
			// Tout le reste est invalide : "10", "(1", "a", "1.5", etc.
			throw std::runtime_error("invalid token");
		}
	}

	// Une expression bien formée laisse exactement un résultat sur la pile.
	if (_stack.size() != 1)
		throw std::runtime_error("malformed expression");

	return _stack.top();
}