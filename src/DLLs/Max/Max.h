/**
 * @file
 * @brief max function
 * @authors Pavlov Ilya
 */

#pragma once

#include "../../include/PluginsLoader.h"

 /**
  * Function max of two values
  * @see IFunction
  */
class Max : public IFunction {
public:
  std::string Name() const noexcept override;
  int NumOfParams() const noexcept override;
  double operator()(const std::vector<double>&) const noexcept override;
};

extern "C" _declspec(dllexport) void on_load(const OperationsRegistrar & reg);
