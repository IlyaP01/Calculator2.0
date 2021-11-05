#include "Trig.h"

std::string Sin::Name() const noexcept {
  return "sin";
}

int Sin::NumOfParams() const noexcept {
  return 1;
}

double Sin::operator()(const std::vector<double>& v) const noexcept {
  return sin(v[0]);
}

std::string Pi::Name() const noexcept {
  return "pi";
}

int Pi::NumOfParams() const noexcept {
  return 0;
}

double Pi::operator()(const std::vector<double>&) const noexcept {
  return 3.14159265358979323846;
}

void on_load(const OperationsRegistrar& reg) {
  reg.AddFunction(new Sin);
  reg.AddFunction(new Pi);
}
