// ExpressionParser.h
// Responsible for tokenizing and converting infix expressions to postfix notation

#pragma once

#include "Exceptions.h"

#include <cstddef>
#include <string>
#include <unordered_map>
#include <vector>

namespace sci_calc {

enum class TokenType {
    Number,
    Operator,
    Function,
    OpenParen,
    CloseParen,
    Constant
};

struct Token {
    TokenType type;
    std::string text;
    double value = 0.0;
};

struct OperatorInfo {
    int precedence;
    bool rightAssociative;
    int arity;
};

class ExpressionParser {
public:
    ExpressionParser();

    std::vector<Token> parseToPostfix(const std::string &expression) const;

private:
    std::unordered_map<std::string, OperatorInfo> operators_;
    std::unordered_map<std::string, double> constants_;

    static bool isIdentifierChar(char ch);
    Token parseNumber(const std::string &expression, std::size_t &index) const;
    Token parseIdentifier(const std::string &expression, std::size_t &index) const;
    Token parseOperator(const std::string &expression, std::size_t &index,
                        const std::vector<Token> &output) const;

    bool isUnaryOperator(const std::string &expression, std::size_t index,
                         const std::vector<Token> &output) const;
};

} // namespace sci_calc


