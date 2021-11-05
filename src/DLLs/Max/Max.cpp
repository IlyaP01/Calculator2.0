#include "Max.h"

std::string Max::Name() const noexcept {
  return "max";
}

int Max::NumOfParams() const noexcept {
  return 2;
}

double Max::operator()(const std::vector<double>& v) const noexcept {
  return v[0] > v[1] ? v[0] : v[1];
}

void on_load(const OperationsRegistrar& reg) {
  reg.AddFunction(new Max);
}
