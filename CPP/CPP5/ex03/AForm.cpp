#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm() : _name("default"), _isSigned(false), _gradeToSign(75), _gradeToExecute(75) {
}

AForm::AForm(const std::string& name, int gradeToSign, int gradeToExecute)
    : _name(name), _isSigned(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute) {
    if (gradeToSign < 1 || gradeToExecute < 1)
        throw GradeTooHighException();
    if (gradeToSign > 150 || gradeToExecute > 150)
        throw GradeTooLowException();
}

AForm::AForm(const AForm& other)
    : _name(other._name), _isSigned(other._isSigned),
      _gradeToSign(other._gradeToSign), _gradeToExecute(other._gradeToExecute) {
}

AForm& AForm::operator=(const AForm& other) {
    if (this != &other)
        _isSigned = other._isSigned;
    return *this;
}

AForm::~AForm() {
}

std::string AForm::getName() const       { return _name; }
bool        AForm::getIsSigned() const   { return _isSigned; }
int         AForm::getGradeToSign() const    { return _gradeToSign; }
int         AForm::getGradeToExecute() const { return _gradeToExecute; }

void AForm::beSigned(const Bureaucrat& b) {
    if (b.getGrade() > _gradeToSign)
        throw GradeTooLowException();
    if (_isSigned)
        throw AlreadySignedException();
    _isSigned = true;
}

// Vérifie les conditions — appelé par chaque classe concrète
void AForm::execute(Bureaucrat const& executor) const {
    if (!_isSigned)
        throw NotSignedException();
    if (executor.getGrade() > _gradeToExecute)
        throw GradeTooLowException();
    doExecute(executor);  // délègue l'action à la classe concrète
}

const char* AForm::GradeTooHighException::what() const throw() {
    return "Form grade too high!";
}

const char* AForm::GradeTooLowException::what() const throw() {
    return "Form grade too low!";
}

const char* AForm::AlreadySignedException::what() const throw() {
    return "Form is already signed!";
}

const char* AForm::NotSignedException::what() const throw() {
    return "Form is not signed!";
}

std::ostream& operator<<(std::ostream& os, const AForm& f) {
    os << "Form " << f.getName()
       << " | signed: " << (f.getIsSigned() ? "yes" : "no")
       << " | grade to sign: " << f.getGradeToSign()
       << " | grade to execute: " << f.getGradeToExecute();
    return os;
}