#pragma once

#include <string>

class IOperation {
public:
  virtual std::string Name() const noexcept = 0;
};