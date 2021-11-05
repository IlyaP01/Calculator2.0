#pragma once

#include "../../include/PluginsLoader.h"

class Sin : public IFunction {
public:
  std::string Name() const noexcept override;
  int NumOfParams() const noexcept override;
  double operator()(const std::vector<double>&) const noexcept override;
};

class Pi : public IFunction {
public:
  std::string Name() const noexcept override;
  int NumOfParams() const noexcept override;
  double operator()(const std::vector<double>&) const noexcept override;
};

extern "C" _declspec(dllexport) void on_load(const OperationsRegistrar & reg);
