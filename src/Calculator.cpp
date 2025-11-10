// Calculator.cpp

#include "Calculator.h"

namespace sci_calc {

Calculator::Calculator() : parser_(), evaluator_() {
}

double Calculator::calculate(const std::string &expression) {
    if (expression.empty()) {
        throw InvalidInputException("Empty expression");
    }

    std::vector<Token> postfixTokens = parser_.parseToPostfix(expression);
    return evaluator_.evaluate(postfixTokens);
}

} // namespace sci_calc


