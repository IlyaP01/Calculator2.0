#pragma once

#include "../../include/PluginsLoader.h"

class Plus : public IBinaryOperator {
public:
  std::string Name() const noexcept override;
  AssocType GetAssocType() const noexcept override;
  double operator()(double lhs, double rhs) const noexcept override;
  int Priority() const noexcept override;
};

class Minus : public IBinaryOperator {
public:
  std::string Name() const noexcept override;
  AssocType GetAssocType() const noexcept override;
  double operator()(double lhs, double rhs) const noexcept override;
  int Priority() const noexcept override;
};

class Mul : public IBinaryOperator {
public:
  std::string Name() const noexcept override;
  AssocType GetAssocType() const noexcept override;
  double operator()(double lhs, double rhs) const noexcept override;
  int Priority() const noexcept override;
};

class Div : public IBinaryOperator {
public:
  std::string Name() const noexcept override;
  AssocType GetAssocType() const noexcept override;
  double operator()(double lhs, double rhs) const noexcept override;
  int Priority() const noexcept override;
};

class UnaryMinus : public IUnaryOperator {
public:
  std::string Name() const noexcept override;
  AffixType GetAffixType() const noexcept override;
  double operator()(double val) const noexcept override;
};

class Comma : public IUnaryOperator {
public:
  std::string Name() const noexcept override;
  AffixType GetAffixType() const noexcept override;
  double operator()(double val) const noexcept override;
};

extern "C" _declspec(dllexport) void on_load(const OperationsRegistrar& reg);
