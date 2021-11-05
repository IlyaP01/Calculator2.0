#pragma once

#include <vector>
#include "IOperation.h"

class IFunction : public IOperation {
public:
  virtual int NumOfParams() const noexcept = 0;
  virtual double operator()(const std::vector<double>&) const = 0;
};
