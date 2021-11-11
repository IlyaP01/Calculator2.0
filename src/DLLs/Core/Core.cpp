#include "Core.h"

std::string Plus::Name() const noexcept {
  return "+";
}

IBinaryOperator::AssocType Plus::GetAssocType() const noexcept {
  return AssocType::LEFT;
}

double Plus::operator()(double lhs, double rhs) const noexcept {
  return lhs + rhs;
}

int Plus::Priority() const noexcept {
  return PLUS_PRIORITY;
}

std::string Minus::Name() const noexcept {
  return "-";
}

IBinaryOperator::AssocType Minus::GetAssocType() const noexcept {
  return AssocType::LEFT;
}

double Minus::operator()(double lhs, double rhs) const noexcept {
  return lhs - rhs;
}

int Minus::Priority() const noexcept {
  return PLUS_PRIORITY;
}

std::string Mul ::Name() const noexcept {
  return "*";
}

IBinaryOperator::AssocType Mul::GetAssocType() const noexcept {
  return AssocType::LEFT;
}

double Mul::operator()(double lhs, double rhs) const noexcept {
  return lhs * rhs;
}

int Mul::Priority() const noexcept {
  return MUL_PRIORITY;
}

std::string Div::Name() const noexcept {
  return "/";
}

IBinaryOperator::AssocType Div::GetAssocType() const noexcept {
  return AssocType::LEFT;
}

double Div::operator()(double lhs, double rhs) const noexcept {
  return lhs / rhs;
}

int Div::Priority() const noexcept {
  return MUL_PRIORITY;
}

std::string Comma::Name() const noexcept {
  return ",";
}

IUnaryOperator::AffixType Comma::GetAffixType() const noexcept {
  return AffixType::POSTFIX;
}

double Comma::operator()(double val) const noexcept {
  return val;
}


void on_load(const OperationsRegistrar& reg) {
  reg.AddBinaryOperator(new Plus);
  reg.AddBinaryOperator(new Minus);
  reg.AddBinaryOperator(new Mul);
  reg.AddBinaryOperator(new Div);
  reg.AddUnaryOperator(new Comma);
}
