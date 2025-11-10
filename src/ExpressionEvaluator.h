// ExpressionEvaluator.h
// Evaluates postfix expression tokens and performs mathematical operations

#pragma once

#include "ExpressionParser.h"
#include "Exceptions.h"

#include <stack>
#include <vector>
#include <cmath>

namespace sci_calc {

class ExpressionEvaluator {
public:
    double evaluate(const std::vector<Token> &postfixTokens) const;

private:
    double applyOperator(const std::string &op, double a, double b) const;
    double applyUnaryOperator(const std::string &op, double a) const;
    double applyFunction(const std::string &func, double arg) const;
};

} // namespace sci_calc


