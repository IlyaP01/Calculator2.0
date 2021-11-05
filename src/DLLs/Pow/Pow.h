#pragma once

#include "../../include/PluginsLoader.h"

class Pow : public IBinaryOperator {
public:
  std::string Name() const noexcept override;
  AssocType GetAssocType() const noexcept override;
  double operator()(double lhs, double rhs) const noexcept override;
  int Priority() const noexcept override;
};

extern "C" _declspec(dllexport) void on_load(const OperationsRegistrar & reg);
