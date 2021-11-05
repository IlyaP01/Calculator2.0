#pragma once

#include <string>
#include "../include/PluginsLoader.h"
class Calculator {
private:
  PluginsLoader loader;
public:
  Calculator();
  double Calculate(const std::string& expression);
};
