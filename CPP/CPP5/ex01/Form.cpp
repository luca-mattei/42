#include "Form.hpp"

//canonical form
Form::Form() : _name("default"), _isSigned(false), _gradeToSign(75), _gradeToExecute(50) {}

Form::Form(const std::string& name, int gradeToSign, int gradeToExecute)
    : _name(name), _isSigned(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute) {
    if (gradeToSign < 1 || gradeToExecute < 1)
        throw GradeTooHighException();
    if (gradeToSign > 150 || gradeToExecute > 150)
        throw GradeTooLowException();
}

Form::Form(const Form& other)
    : _name(other._name), _isSigned(other._isSigned),
      _gradeToSign(other._gradeToSign), _gradeToExecute(other._gradeToExecute) {}

Form& Form::operator=(const Form& other) {
    if (this != &other)
        _isSigned = other._isSigned;
    return *this;
}

Form::~Form() {}

//mes getters
std::string Form::getName() const { return _name; }
bool        Form::getIsSigned() const { return _isSigned; }
int         Form::getGradeToSign() const { return _gradeToSign; }
int         Form::getGradeToExecute() const { return _gradeToExecute; }

//fonction membre 
void Form::beSigned(const Bureaucrat& b) {
    if (b.getGrade() > _gradeToSign)
        throw GradeTooLowException();
    if (_isSigned)
        throw AlreadySignedException();
    _isSigned = true;
}
//exceptions
const char* Form::GradeTooHighException::what() const throw() {
    return "Form grade too high!";
}

const char* Form::GradeTooLowException::what() const throw() {
    return "Form grade too low!";
}

const char* Form::AlreadySignedException::what() const throw() {
    return "Form already signed!";
}
//surcharge de l'opérateur
std::ostream& operator<<(std::ostream& os, const Form& f) {
    os << "Form " << f.getName()
       << " | signed: " << (f.getIsSigned() ? "yes" : "no")
       << " | grade to sign: " << f.getGradeToSign()
       << " | grade to execute: " << f.getGradeToExecute();
    return os;
}