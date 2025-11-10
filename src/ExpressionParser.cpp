// ExpressionParser.cpp

#include "ExpressionParser.h"

#include <algorithm>
#include <cctype>
#include <stack>

namespace sci_calc {

namespace {

std::string toLower(std::string text) {
    std::transform(text.begin(), text.end(), text.begin(), [](unsigned char ch) {
        return static_cast<char>(std::tolower(ch));
    });
    return text;
}

} // namespace

ExpressionParser::ExpressionParser() {
    operators_.emplace("+", OperatorInfo{2, false, 2});
    operators_.emplace("-", OperatorInfo{2, false, 2});
    operators_.emplace("*", OperatorInfo{3, false, 2});
    operators_.emplace("/", OperatorInfo{3, false, 2});
    operators_.emplace("%", OperatorInfo{3, false, 2});
    operators_.emplace("^", OperatorInfo{4, true, 2});
    operators_.emplace("neg", OperatorInfo{5, true, 1});

    constants_.emplace("pi", 3.14159265358979323846);
    constants_.emplace("e", 2.71828182845904523536);
}

std::vector<Token> ExpressionParser::parseToPostfix(const std::string &expression) const {
    std::vector<Token> output;
    std::stack<Token> stack;

    std::size_t i = 0;
    while (i < expression.size()) {
        char ch = expression[i];

        if (std::isspace(static_cast<unsigned char>(ch))) {
            ++i;
            continue;
        }

        if (std::isdigit(static_cast<unsigned char>(ch)) ||
            (ch == '.' && i + 1 < expression.size() &&
             std::isdigit(static_cast<unsigned char>(expression[i + 1])))) {
            output.push_back(parseNumber(expression, i));
            continue;
        }

        if (isIdentifierChar(ch)) {
            Token identifier = parseIdentifier(expression, i);
            if (identifier.type == TokenType::Constant) {
                output.push_back(identifier);
            } else {
                stack.push(identifier);
            }
            continue;
        }

        if (ch == ',') {
            // Function argument separator is unsupported (all functions are unary)
            throw InvalidInputException("Unexpected ',' in expression: multiple arguments not supported");
        }

        if (ch == '(') {
            stack.push(Token{TokenType::OpenParen, "(", 0.0});
            ++i;
            continue;
        }

        if (ch == ')') {
            ++i;
            bool foundOpenParen = false;
            while (!stack.empty()) {
                Token top = stack.top();
                stack.pop();
                if (top.type == TokenType::OpenParen) {
                    foundOpenParen = true;
                    break;
                }
                output.push_back(top);
            }

            if (!foundOpenParen) {
                throw InvalidInputException("Unmatched ')' in expression");
            }

            if (!stack.empty() && stack.top().type == TokenType::Function) {
                output.push_back(stack.top());
                stack.pop();
            }
            continue;
        }

        // Operators
        Token opToken = parseOperator(expression, i, output);

        while (!stack.empty()) {
            const Token &top = stack.top();
            if (top.type != TokenType::Operator) {
                break;
            }

            const auto &currentInfo = operators_.at(opToken.text);
            const auto &topInfo = operators_.at(top.text);

            bool shouldPop = (!currentInfo.rightAssociative && currentInfo.precedence <= topInfo.precedence) ||
                             (currentInfo.rightAssociative && currentInfo.precedence < topInfo.precedence);

            if (!shouldPop) {
                break;
            }

            output.push_back(top);
            stack.pop();
        }

        stack.push(opToken);
    }

    while (!stack.empty()) {
        Token top = stack.top();
        stack.pop();
        if (top.type == TokenType::OpenParen || top.type == TokenType::CloseParen) {
            throw InvalidInputException("Unmatched '(' in expression");
        }
        output.push_back(top);
    }

    return output;
}

bool ExpressionParser::isIdentifierChar(char ch) {
    return std::isalpha(static_cast<unsigned char>(ch)) || ch == '_';
}

Token ExpressionParser::parseNumber(const std::string &expression, std::size_t &index) const {
    std::size_t start = index;
    bool hasDecimalPoint = false;

    while (index < expression.size()) {
        char ch = expression[index];
        if (std::isdigit(static_cast<unsigned char>(ch))) {
            ++index;
            continue;
        }
        if (ch == '.' && !hasDecimalPoint) {
            hasDecimalPoint = true;
            ++index;
            continue;
        }
        if ((ch == 'e' || ch == 'E') && index + 1 < expression.size()) {
            std::size_t expIndex = index + 1;
            if (expression[expIndex] == '+' || expression[expIndex] == '-') {
                ++expIndex;
            }
            if (expIndex >= expression.size() ||
                !std::isdigit(static_cast<unsigned char>(expression[expIndex]))) {
                throw InvalidInputException("Malformed exponent in number literal");
            }
            index = expIndex + 1;
            while (index < expression.size() &&
                   std::isdigit(static_cast<unsigned char>(expression[index]))) {
                ++index;
            }
            break;
        }
        break;
    }

    const std::string literal = expression.substr(start, index - start);
    try {
        double value = std::stod(literal);
        return Token{TokenType::Number, literal, value};
    } catch (const std::exception &) {
        throw InvalidInputException("Unable to parse number literal: " + literal);
    }
}

Token ExpressionParser::parseIdentifier(const std::string &expression, std::size_t &index) const {
    std::size_t start = index;
    while (index < expression.size() &&
           (isIdentifierChar(expression[index]) ||
            std::isdigit(static_cast<unsigned char>(expression[index])))) {
        ++index;
    }

    std::string identifier = expression.substr(start, index - start);
    std::string lower = toLower(identifier);

    auto constantIt = constants_.find(lower);
    if (constantIt != constants_.end()) {
        return Token{TokenType::Constant, lower, constantIt->second};
    }

    static const std::unordered_map<std::string, int> functions = {
        {"sin", 1}, {"cos", 1}, {"tan", 1}, {"asin", 1}, {"acos", 1}, {"atan", 1},
        {"log", 1}, {"ln", 1}, {"sqrt", 1}, {"exp", 1}, {"abs", 1}};

    if (functions.find(lower) != functions.end()) {
        return Token{TokenType::Function, lower, 0.0};
    }

    throw InvalidInputException("Unknown identifier: " + identifier);
}

bool ExpressionParser::isUnaryOperator(const std::string &expression, std::size_t index,
                                       const std::vector<Token> &output) const {
    if (index == 0) {
        return true;
    }

    std::size_t prevIndex = index;
    while (prevIndex > 0) {
        char prevChar = expression[prevIndex - 1];
        if (std::isspace(static_cast<unsigned char>(prevChar))) {
            --prevIndex;
            continue;
        }
        break;
    }

    if (prevIndex == 0) {
        return true;
    }

    char prevChar = expression[prevIndex - 1];

    if (prevChar == '(' || prevChar == ',' || operators_.count(std::string(1, prevChar)) > 0) {
        return true;
    }

    if (!output.empty()) {
        Token lastToken = output.back();
        if (lastToken.type == TokenType::Operator) {
            return true;
        }
    }

    return false;
}

Token ExpressionParser::parseOperator(const std::string &expression, std::size_t &index,
                                      const std::vector<Token> &output) const {
    char ch = expression[index];
    std::string op(1, ch);

    if (ch == '+' || ch == '-') {
        if (isUnaryOperator(expression, index, output)) {
            ++index;
            return Token{TokenType::Operator, ch == '-' ? "neg" : "+", 0.0};
        }
    }

    if (operators_.find(op) == operators_.end()) {
        throw InvalidInputException(std::string("Unsupported operator: ") + ch);
    }

    ++index;
    return Token{TokenType::Operator, op, 0.0};
}

} // namespace sci_calc


