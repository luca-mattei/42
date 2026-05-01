#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm()
    : AForm("ShrubberyCreationForm", 145, 137), _target("default") {
}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target)
    : AForm("ShrubberyCreationForm", 145, 137), _target(target) {
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& other)
    : AForm(other), _target(other._target) {
}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& other) {
    if (this != &other) {
        AForm::operator=(other);
        _target = other._target;
    }
    return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm() {
}

void ShrubberyCreationForm::doExecute(Bureaucrat const& executor) const {
    (void)executor;
    std::ofstream file((_target + "_shrubbery").c_str());
    if (!file.is_open())
        throw std::exception();
    file << "       *       " << std::endl;
    file << "      ***      " << std::endl;
    file << "     *****     " << std::endl;
    file << "    *******    " << std::endl;
    file << "   *********   " << std::endl;
    file << "  ***********  " << std::endl;
    file << "      |||      " << std::endl;
    file << "      |||      " << std::endl;
    file.close();
}