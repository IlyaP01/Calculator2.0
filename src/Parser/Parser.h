/**
 * @file
 * @brief Parser class header file
 * @authors Pavlov Ilya
 *
 * Contains Parser and Token classes declarationss
 */

#pragma once

#include <string>
#include <vector>
#include <variant>
#include "../include/IOperation.h"
#include "../include/IFunction.h"
#include "../include/IOperator.h"
#include "../include/PluginsLoader.h"

/**
 * Just token  
 */
class Token {
public:
  /**
   * Types of token 
   */
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

/**
 * @brief Parser class
 *
 * Class for splitting input expression into tokens
 */
class Parser {
private:
  const std::string& expr;
  std::vector<Token*> tokens;
  size_t curIndex = 0;
  bool end = false;
  const PluginsLoader& loader;

  void HandleOperation(Token* newToken);
  void HandleNumber(Token* newToken);
  void SkipSpaces();
public:
  /**
   * Constructor
   * @param[in] expression expression to split
   * @param[in] loader plugins loader with information about loaded operations
   */
  Parser(const std::string& expression, const PluginsLoader& loader);

  /**
   * Function for getting tokens (works like output iterator) 
   * @return next token
   */
  Token* GetNextToken();

  /**
   * End of tokens flag
   * @return true if there are no more tokens else false
   */
  bool IsEnd() const noexcept;
  
  /**
   * Destructor 
   */
  ~Parser();
};