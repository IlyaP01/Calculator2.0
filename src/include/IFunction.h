/**
 * @file
 * @brief IFunction header file
 * @authors Pavlov Ilya
 *
 * Contains IFunction pure virtual class declaration
 */

#pragma once

#include <vector>
#include "IOperation.h"

/**
 * Interface for all loaded functions 
 */
class IFunction : public IOperation {
public:
  /**
   * Number of function parametres 
   * @return number of parametres 
   */
  virtual int NumOfParams() const noexcept = 0;

  /**
   * Calculate the value of function
   * @return result
   */
  virtual double operator()(const std::vector<double>&) const = 0;
};
