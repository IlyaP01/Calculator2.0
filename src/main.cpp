#include "Calculator/Calculator.h"
#include <iostream>
#include <Windows.h>

int main() {
  Calculator calc;
  std::string line;

  while (!std::getline(std::cin, line).eof()) {
    if (line.empty())
      continue;
    try {
      double result = calc.Calculate(line);
      std::cout << line << " = " << result << std::endl;
    }
    catch (std::exception& e) {
      std::cout << "Error: " << e.what() << std::endl;
    }
  }

  return 0;
}