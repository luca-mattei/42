#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

Intern::Intern() {}
Intern::Intern(const Intern& other) { (void)other; }
Intern& Intern::operator=(const Intern& other) { (void)other; return *this; }
Intern::~Intern() {}

static AForm* makeShrubbery(const std::string& target) {
    return new ShrubberyCreationForm(target);
}
static AForm* makeRobotomy(const std::string& target) {
    return new RobotomyRequestForm(target);
}
static AForm* makePardon(const std::string& target) {
    return new PresidentialPardonForm(target);
}

AForm* Intern::makeForm(const std::string& formName, const std::string& target) const {
    struct FormEntry {
        std::string name;
        AForm*      (*creator)(const std::string&);
    };

    FormEntry forms[] = {
        { "shrubbery creation",  makeShrubbery },
        { "robotomy request",    makeRobotomy  },
        { "presidential pardon", makePardon    }
    };

    for (int i = 0; i < 3; i++) {
        if (forms[i].name == formName) {
            std::cout << "Intern creates " << formName << std::endl;
            return forms[i].creator(target);
        }
    }

    std::cout << "Intern: unknown form '" << formName << "'" << std::endl;
    return NULL;
}