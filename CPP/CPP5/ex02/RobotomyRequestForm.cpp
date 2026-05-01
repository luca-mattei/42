#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm()
    : AForm("RobotomyRequestForm", 72, 45), _target("default") {
}

RobotomyRequestForm::RobotomyRequestForm(const std::string& target)
    : AForm("RobotomyRequestForm", 72, 45), _target(target) {
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& other)
    : AForm(other), _target(other._target) {
}

RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm& other) {
    if (this != &other) {
        AForm::operator=(other);
        _target = other._target;
    }
    return *this;
}

RobotomyRequestForm::~RobotomyRequestForm() {
}

void RobotomyRequestForm::doExecute(Bureaucrat const& executor) const {
    (void)executor;
    std::cout << "DRRRRRRRR BZZZZZZZ DRRRRRR..." << std::endl;
    // rand() % 2 → 0 ou 1, 50% de chance chacun
    if (std::rand() % 2)
        std::cout << _target << " has been robotomized successfully!" << std::endl;
    else
        std::cout << _target << " robotomy failed!" << std::endl;
}