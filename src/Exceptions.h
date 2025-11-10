// Exceptions.h
// Scientific Calculator custom exception hierarchy

#pragma once

#include <stdexcept>
#include <string>

namespace sci_calc {

class CalculatorException : public std::runtime_error {
public:
    explicit CalculatorException(const std::string &message)
        : std::runtime_error(message) {}
};

class InvalidInputException : public CalculatorException {
public:
    explicit InvalidInputException(const std::string &message)
        : CalculatorException(message) {}
};

class MathDomainException : public CalculatorException {
public:
    explicit MathDomainException(const std::string &message)
        : CalculatorException(message) {}
};

} // namespace sci_calc


