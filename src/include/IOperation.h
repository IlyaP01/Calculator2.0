/**
 * @file
 * @brief IOperation header file
 * @authors Pavlov Ilya
 *
 * Contains IOperation pure virtual class declaration
 */

#pragma once

#include <string>

/**
 * Interface class, common for operators and functions 
 */
class IOperation {
public:
  /** Name of operation in expression (for example + for sum)
   * @return string with name
   */
  virtual std::string Name() const noexcept = 0;
};