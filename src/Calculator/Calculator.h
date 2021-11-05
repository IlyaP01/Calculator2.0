/**
 * @file
 * @brief Calculator class header file
 * @authors Pavlov Ilya
 *
 * Contains Calculator declaration
 */

#pragma once

#include <string>
#include "../include/PluginsLoader.h"

/**
 * Main calculator class
 */
class Calculator {
private:
  PluginsLoader loader;
public:
  /**
   * Constructor 
   */
  Calculator();

  /**
   * Calculate expression
   * @return result of calculation
   */
  double Calculate(const std::string& expression);
};
