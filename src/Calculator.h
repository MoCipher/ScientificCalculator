// Calculator.h
// Main calculator class that coordinates parsing and evaluation

#pragma once

#include "ExpressionParser.h"
#include "ExpressionEvaluator.h"
#include "Exceptions.h"

#include <string>

namespace sci_calc {

class Calculator {
public:
    Calculator();
    
    double calculate(const std::string &expression);

private:
    ExpressionParser parser_;
    ExpressionEvaluator evaluator_;
};

} // namespace sci_calc


