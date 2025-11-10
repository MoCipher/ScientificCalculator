// main.cpp
// Command-line interface for the Scientific Calculator

#include "Calculator.h"

#include <iostream>
#include <string>
#include <iomanip>

void printUsage(const char *programName) {
    std::cout << "Scientific Calculator\n";
    std::cout << "Usage: " << programName << " [expression]\n\n";
    std::cout << "If no expression is provided, the calculator runs in interactive mode.\n\n";
    std::cout << "Supported operations:\n";
    std::cout << "  Basic: +, -, *, /, %, ^ (power)\n";
    std::cout << "  Functions: sin, cos, tan, asin, acos, atan\n";
    std::cout << "             log (base 10), ln (natural), sqrt, exp, abs\n";
    std::cout << "  Constants: pi, e\n";
    std::cout << "\nExamples:\n";
    std::cout << "  " << programName << " \"2 + 3 * 4\"\n";
    std::cout << "  " << programName << " \"sin(pi/2)\"\n";
    std::cout << "  " << programName << " \"sqrt(16) + log(100)\"\n";
    std::cout << "  " << programName << " \"2^3 + 5\"\n";
}

int main(int argc, char *argv[]) {
    sci_calc::Calculator calculator;

    // If expression provided as command-line argument
    if (argc > 1) {
        std::string expression = argv[1];
        if (expression == "-h" || expression == "--help") {
            printUsage(argv[0]);
            return 0;
        }

        try {
            double result = calculator.calculate(expression);
            std::cout << std::fixed << std::setprecision(10) << result << std::endl;
            return 0;
        } catch (const sci_calc::CalculatorException &e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return 1;
        } catch (const std::exception &e) {
            std::cerr << "Unexpected error: " << e.what() << std::endl;
            return 1;
        }
    }

    // Interactive mode
    std::cout << "Scientific Calculator - Interactive Mode\n";
    std::cout << "Enter expressions to evaluate. Type 'quit' or 'exit' to exit.\n";
    std::cout << "Type 'help' for usage information.\n\n";

    std::string line;
    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, line)) {
            break;
        }

        // Trim whitespace
        line.erase(0, line.find_first_not_of(" \t\n\r"));
        line.erase(line.find_last_not_of(" \t\n\r") + 1);

        if (line.empty()) {
            continue;
        }

        if (line == "quit" || line == "exit" || line == "q") {
            std::cout << "Goodbye!\n";
            break;
        }

        if (line == "help" || line == "h") {
            printUsage(argv[0]);
            continue;
        }

        try {
            double result = calculator.calculate(line);
            std::cout << std::fixed << std::setprecision(10) << result << std::endl;
        } catch (const sci_calc::CalculatorException &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        } catch (const std::exception &e) {
            std::cerr << "Unexpected error: " << e.what() << std::endl;
        }
    }

    return 0;
}


