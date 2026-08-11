#include "ScalarConverter.hpp"

//'c' entoure de "\'" et 3 de longueur 1 seul charctere au milieu
static bool isChar(const std::string& s) {
    return s.length() == 3 && s[0] == '\'' && s[2] == '\'';
}

static bool isPseudoLiteral(const std::string& s) {
    return s == "-inff" || s == "+inff" || s == "nanf"
        || s == "-inf"  || s == "+inf"  || s == "nan";
}
//commence par + ou - ou rien, check si tout est digit et si ya qqch apres les eventuels signes
static bool isInt(const std::string& s) {
    size_t i = 0;
    if (s[i] == '-' || s[i] == '+') i++;
    if (i == s.length()) return false;
    for (; i < s.length(); i++)
        if (!std::isdigit(s[i])) return false;
    return true;
}

static bool isFloat(const std::string& s) {
    // doit finir par 'f' et contenir un '.'
    if (s.empty() || s[s.length() - 1] != 'f') return false;
    std::string tmp = s.substr(0, s.length() - 1);
    bool hasDot = false;
    size_t i = 0;
    if (tmp[i] == '-' || tmp[i] == '+') i++;
    if (i == tmp.length()) return false;
    for (; i < tmp.length(); i++) {
        if (tmp[i] == '.') { 
            if (hasDot) return false; // pas 2 points
            hasDot = true;
            continue;   
        }
        if (!std::isdigit(tmp[i])) return false;
    }
    return hasDot;
}

static bool isDouble(const std::string& s) {
    bool hasDot = false;
    size_t i = 0;
    if (s[i] == '-' || s[i] == '+') i++;
    if (i == s.length()) return false;
    for (; i < s.length(); i++) {
        if (s[i] == '.') { hasDot = true; continue; }
        if (!std::isdigit(s[i])) return false;
    }
    return hasDot;
}


static void printChar(double d) {
    if (std::isnan(d) || std::isinf(d))
        std::cout << "char: impossible" << std::endl;
    else if (d < 0 || d > 127)
        std::cout << "char: impossible" << std::endl;
    else if (!std::isprint(static_cast<char>(d)))
        std::cout << "char: Non displayable" << std::endl;
    else
        std::cout << "char: '" << static_cast<char>(d) << "'" << std::endl;
}

static void printInt(double d) {
    if (std::isnan(d) || std::isinf(d))
        std::cout << "int: impossible" << std::endl;
    else if (d < static_cast<double>(INT_MIN) || d > static_cast<double>(INT_MAX))
        std::cout << "int: impossible" << std::endl;
    else
        std::cout << "int: " << static_cast<int>(d) << std::endl;
}

static void printFloat(double d) {
    if (std::isnan(d))
        std::cout << "float: nanf" << std::endl;
    else if (std::isinf(d))
        std::cout << "float: " << (d > 0 ? "+inff" : "-inff") << std::endl;
    else
        std::cout << "float: " << std::fixed << std::setprecision(1)
                  << static_cast<float>(d) << "f" << std::endl;
}

static void printDouble(double d) {
    if (std::isnan(d))
        std::cout << "double: nan" << std::endl;
    else if (std::isinf(d))
        std::cout << "double: " << (d > 0 ? "+inf" : "-inf") << std::endl;
    else
        std::cout << "double: " << std::fixed << std::setprecision(1)
                  << d << std::endl;
}


void ScalarConverter::convert(const std::string& s) {
    double d;

    if (isChar(s)) {
        d = static_cast<double>(s[1]);
    }
    else if (isPseudoLiteral(s)) {
        if (s == "nanf" || s == "nan")
            d = std::numeric_limits<double>::quiet_NaN();
        else if (s == "+inff" || s == "+inf")
            d = std::numeric_limits<double>::infinity();
        else
            d = -std::numeric_limits<double>::infinity();
    }
    else if (isInt(s)) {
        d = std::strtod(s.c_str(), NULL);
    }
    else if (isFloat(s)) {
        d = static_cast<double>(std::atof(s.c_str()));
    }
    else if (isDouble(s)) {
        d = std::atof(s.c_str());
    }
    else {
        std::cout << "Error: unrecognized literal" << std::endl;
        return;
    }

    // Tout passe par double — on affiche les 4 types
    printChar(d);
    printInt(d);
    printFloat(d);
    printDouble(d);
}