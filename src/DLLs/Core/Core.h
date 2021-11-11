/**
 * @file
 * @brief Core operations
 * @authors Pavlov Ilya
 *
 * Contains base operations
 */

#pragma once

#include "../../include/PluginsLoader.h"

/**
 * Operator + 
 * @see IBinaryOperator 
 */
class Plus : public IBinaryOperator {
public:
  std::string Name() const noexcept override;
  AssocType GetAssocType() const noexcept override;
  double operator()(double lhs, double rhs) const noexcept override;
  int Priority() const noexcept override;
};

/**
 * Operator -
 * @see IBinaryOperator
 */
class Minus : public IBinaryOperator {
public:
  std::string Name() const noexcept override;
  AssocType GetAssocType() const noexcept override;
  double operator()(double lhs, double rhs) const noexcept override;
  int Priority() const noexcept override;
};

/**
 * Operator *
 * @see IBinaryOperator
 */
class Mul : public IBinaryOperator {
public:
  std::string Name() const noexcept override;
  AssocType GetAssocType() const noexcept override;
  double operator()(double lhs, double rhs) const noexcept override;
  int Priority() const noexcept override;
};

/**
 * Operator /
 * @see IBinaryOperator
 */
class Div : public IBinaryOperator {
public:
  std::string Name() const noexcept override;
  AssocType GetAssocType() const noexcept override;
  double operator()(double lhs, double rhs) const noexcept override;
  int Priority() const noexcept override;
};

/**
 * Operator ,
 * @see IUnaryOperator
 */
class Comma : public IUnaryOperator {
public:
  std::string Name() const noexcept override;
  AffixType GetAffixType() const noexcept override;
  double operator()(double val) const noexcept override;
};

extern "C" _declspec(dllexport) void on_load(const OperationsRegistrar& reg);
