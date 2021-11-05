#include "Pow.h"

std::string Pow::Name() const noexcept {
  return "^";
}

IBinaryOperator::AssocType Pow::GetAssocType() const noexcept {
  return AssocType::RIGHT;
}

double Pow::operator()(double lhs, double rhs) const noexcept {
  return pow(lhs, rhs);
}

int Pow::Priority() const noexcept {
  return MUL_PRIORITY + 1;
}

void on_load(const OperationsRegistrar& reg) {
  reg.AddBinaryOperator(new Pow);
}
