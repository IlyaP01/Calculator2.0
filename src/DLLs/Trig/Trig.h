/**
 * @file
 * @brief trigonometry functions
 * @authors Pavlov Ilya
 */

#pragma once

#include "../../include/PluginsLoader.h"

 /**
  * Function sin
  * @see IFunction
  */
class Sin : public IFunction {
public:
  std::string Name() const noexcept override;
  int NumOfParams() const noexcept override;
  double operator()(const std::vector<double>&) const noexcept override;
};

/**
 * Constant pi (function without arguments)
 * @see IFunction
 */
class Pi : public IFunction {
public:
  std::string Name() const noexcept override;
  int NumOfParams() const noexcept override;
  double operator()(const std::vector<double>&) const noexcept override;
};

extern "C" _declspec(dllexport) void on_load(const OperationsRegistrar & reg);
