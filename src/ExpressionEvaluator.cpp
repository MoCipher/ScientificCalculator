// ExpressionEvaluator.cpp

#include "ExpressionEvaluator.h"

#include <stdexcept>

namespace sci_calc {

double ExpressionEvaluator::evaluate(const std::vector<Token> &postfixTokens) const {
    std::stack<double> stack;

    for (const auto &token : postfixTokens) {
        switch (token.type) {
            case TokenType::Number:
            case TokenType::Constant:
                stack.push(token.value);
                break;

            case TokenType::Operator: {
                if (stack.size() < 1) {
                    throw InvalidInputException("Insufficient operands for operator: " + token.text);
                }

                if (token.text == "neg" || token.text == "pos") {
                    double a = stack.top();
                    stack.pop();
                    stack.push(applyUnaryOperator(token.text, a));
                } else {
                    if (stack.size() < 2) {
                        throw InvalidInputException("Insufficient operands for binary operator: " + token.text);
                    }
                    double b = stack.top();
                    stack.pop();
                    double a = stack.top();
                    stack.pop();
                    stack.push(applyOperator(token.text, a, b));
                }
                break;
            }

            case TokenType::Function: {
                if (stack.empty()) {
                    throw InvalidInputException("Insufficient operands for function: " + token.text);
                }
                double arg = stack.top();
                stack.pop();
                stack.push(applyFunction(token.text, arg));
                break;
            }

            default:
                throw InvalidInputException("Unexpected token type in postfix expression");
        }
    }

    if (stack.size() != 1) {
        throw InvalidInputException("Invalid expression: stack contains " + 
                                   std::to_string(stack.size()) + " values");
    }

    return stack.top();
}

double ExpressionEvaluator::applyOperator(const std::string &op, double a, double b) const {
    if (op == "+") {
        return a + b;
    } else if (op == "-") {
        return a - b;
    } else if (op == "*") {
        return a * b;
    } else if (op == "/") {
        if (std::abs(b) < 1e-10) {
            throw MathDomainException("Division by zero");
        }
        return a / b;
    } else if (op == "%") {
        if (std::abs(b) < 1e-10) {
            throw MathDomainException("Modulo by zero");
        }
        return std::fmod(a, b);
    } else if (op == "^") {
        if (a < 0 && std::fmod(b, 1.0) != 0.0) {
            throw MathDomainException("Cannot raise negative number to non-integer power");
        }
        double result = std::pow(a, b);
        if (std::isnan(result) || std::isinf(result)) {
            throw MathDomainException("Power operation resulted in invalid value");
        }
        return result;
    } else {
        throw InvalidInputException("Unknown operator: " + op);
    }
}

double ExpressionEvaluator::applyUnaryOperator(const std::string &op, double a) const {
    if (op == "neg") {
        return -a;
    } else if (op == "pos") {
        return a;
    } else {
        throw InvalidInputException("Unknown unary operator: " + op);
    }
}

double ExpressionEvaluator::applyFunction(const std::string &func, double arg) const {
    if (func == "sin") {
        return std::sin(arg);
    } else if (func == "cos") {
        return std::cos(arg);
    } else if (func == "tan") {
        double result = std::tan(arg);
        if (std::isinf(result) || std::isnan(result)) {
            throw MathDomainException("Tangent is undefined for the given angle");
        }
        return result;
    } else if (func == "asin") {
        if (arg < -1.0 || arg > 1.0) {
            throw MathDomainException("Arcsin argument must be in range [-1, 1]");
        }
        return std::asin(arg);
    } else if (func == "acos") {
        if (arg < -1.0 || arg > 1.0) {
            throw MathDomainException("Arccos argument must be in range [-1, 1]");
        }
        return std::acos(arg);
    } else if (func == "atan") {
        return std::atan(arg);
    } else if (func == "log") {
        if (arg <= 0.0) {
            throw MathDomainException("Logarithm argument must be positive");
        }
        return std::log10(arg);
    } else if (func == "ln") {
        if (arg <= 0.0) {
            throw MathDomainException("Natural logarithm argument must be positive");
        }
        return std::log(arg);
    } else if (func == "sqrt") {
        if (arg < 0.0) {
            throw MathDomainException("Square root of negative number is not a real number");
        }
        return std::sqrt(arg);
    } else if (func == "exp") {
        double result = std::exp(arg);
        if (std::isinf(result)) {
            throw MathDomainException("Exponential overflow");
        }
        return result;
    } else if (func == "abs") {
        return std::abs(arg);
    } else {
        throw InvalidInputException("Unknown function: " + func);
    }
}

} // namespace sci_calc


