#pragma once

#include <string>
#include <vector>
#include <variant>
#include "../include/IOperation.h"
#include "../include/IFunction.h"
#include "../include/IOperator.h"
#include "../include/PluginsLoader.h"

class Token {
public:
  enum class Type {
    NUMBER,
    BIN_OPERATOR,
    UN_OPERATOR,
    FUNCTION,
    OPN_BRACKET,
    CLS_BRACKET,
  };
  Type type;
  std::variant<std::monostate, double, IOperation*> val;
};

class Parser {
private:
  const std::string& expr;
  std::vector<Token*> tokens;
  size_t curIndex = 0;
  bool end = false;
  const PluginsLoader& loader;
public:
  Parser(const std::string& expression, const PluginsLoader& loader);
  Token* GetNextToken();
  bool IsEnd();
  ~Parser();
};