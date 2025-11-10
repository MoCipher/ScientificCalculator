# ScientificCalculator

A feature-rich scientific calculator implemented in C++ that provides advanced mathematical operations and a user-friendly interface.

## Features

- **Basic Arithmetic Operations**: Addition, subtraction, multiplication, and division
- **Advanced Mathematical Functions**: 
  - Trigonometric functions (sin, cos, tan)
  - Inverse trigonometric functions (asin, acos, atan)
  - Logarithmic functions (log, log10)
  - Exponential functions (exp, pow)
  - Square root and power operations
- **Memory Functions**: Store, recall, and clear memory values
- **Error Handling**: Comprehensive error detection and user-friendly error messages
- **Clean Interface**: Simple and intuitive command-line interface

## Requirements

- C++ compiler (C++11 or later recommended)
- Standard C++ library only (no external dependencies)

## Building the Project

### Prerequisites
- C++ compiler (g++, clang++, or MSVC)
- CMake (optional, for automated builds)

### Compilation

#### Using g++ (Linux/macOS)
```bash
g++ -std=c++11 -o ScientificCalculator main.cpp calculator.cpp
```

#### Using Makefile
```bash
make
```

#### Using CMake
```bash
mkdir build
cd build
cmake ..
make
```

## Usage

1. **Run the executable**:
   ```bash
   ./ScientificCalculator
   ```

2. **Basic Operations**:
   ```
   Enter an expression or command: 5 + 3
   Result: 8
   ```

3. **Advanced Functions**:
   ```
   Enter an expression or command: sin(30)
   Result: 0.5
   ```

4. **Memory Operations**:
   ```
   Enter an expression or command: memstore 10
   Enter an expression or command: memadd 5
   Enter an expression or command: memrecall
   Result: 15
   ```

5. **Exit the calculator**:
   ```
   Enter an expression or command: exit
   ```

## Supported Operations

### Basic Arithmetic
- `+` : Addition
- `-` : Subtraction
- `*` : Multiplication
- `/` : Division
- `^` : Power operation

### Trigonometric Functions
- `sin(x)` : Sine
- `cos(x)` : Cosine
- `tan(x)` : Tangent
- `asin(x)` : Arcsine
- `acos(x)` : Arccosine
- `atan(x)` : Arctangent

### Logarithmic and Exponential Functions
- `log(x)` : Natural logarithm
- `log10(x)` : Base-10 logarithm
- `exp(x)` : Exponential function
- `sqrt(x)` : Square root
- `pow(x, y)` : Power function

### Memory Functions
- `memstore x` : Store value in memory
- `memadd x` : Add value to memory
- `memsubtract x` : Subtract value from memory
- `memrecall` : Recall memory value
- `memclear` : Clear memory

## Project Structure

```
ScientificCalculator/
├── main.cpp              # Main program entry point
├── calculator.cpp        # Core calculator implementation
├── calculator.h          # Calculator class header
├── README.md             # This file
└── Makefile              # Build configuration (optional)
```

## Code Structure

### Calculator Class
The main calculator functionality is implemented in the `Calculator` class, which provides:
- Expression parsing and evaluation
- Mathematical function implementations
- Memory management
- Error handling

### Key Components
- **Expression Parser**: Handles input parsing and tokenization
- **Evaluator**: Processes mathematical expressions and computes results
- **Function Library**: Implements all supported mathematical functions
- **Memory Manager**: Handles storage and retrieval of memory values

## Error Handling

The calculator includes comprehensive error handling for:
- Invalid expressions
- Division by zero
- Domain errors (logarithm of negative numbers, etc.)
- Memory overflow/underflow
- Syntax errors

Error messages are user-friendly and provide guidance for correct usage.

## Examples

### Basic Calculations
```
Enter an expression or command: 15 * 4 + 10 / 2
Result: 65

Enter an expression or command: 2 ^ 10
Result: 1024
```

### Scientific Calculations
```
Enter an expression or command: sin(45) + cos(45)
Result: 1.41421

Enter an expression or command: log(100) * exp(2)
Result: 18.4207
```

### Memory Operations
```
Enter an expression or command: memstore 25
Enter an expression or command: memadd 15
Enter an expression or command: memrecall
Result: 40
```

## Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Test thoroughly
5. Submit a pull request

## License

This project is open source and available under the MIT License.

## Future Enhancements

- Graphical user interface (GUI) implementation
- Additional mathematical functions (hyperbolic functions, statistical functions)
- Expression history and recall
- Custom variable storage
- Unit conversion capabilities
- Complex number support

## Contact

For questions, suggestions, or contributions, please open an issue on the GitHub repository.
