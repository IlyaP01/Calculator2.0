/**
 * @file
 * @brief Parser class source file
 * @authors Pavlov Ilya
 *
 * Contains Parser definition
 */

#include "Parser.h"
#include <assert.h>
#include <stdexcept>

 /**
  * Constructor
  * @param[in] expression expression to split
  * @param[in] loader plugins loader with information about loaded operations
  */
Parser::Parser(const std::string& expression, const PluginsLoader& loader) : expr(expression), loader(loader) {}

void Parser::SkipSpaces() {
  while (curIndex < expr.length() && isspace(expr[curIndex])) {
    ++curIndex;
  }
}

void Parser::HandleNumber(Token* newToken) {
  try {
    size_t posDiff;
    double val = std::stod(&expr[curIndex], &posDiff);
    newToken->type = Token::Type::NUMBER;
    newToken->val = val;
    curIndex += posDiff;
  }
  catch (std::invalid_argument&) {
    throw std::exception("invalid number");
  }
  catch (std::out_of_range&) {
    throw std::exception("number is too big");
  }
}

static size_t _findNameLength(const std::string& expr, size_t index) {
  size_t startIndex = index;
  char sym = expr[index];
  while (index < expr.length() && !isspace(sym) && !isdigit(sym) && sym != '(' && sym != ')') {
    sym = expr[++index];
  }

  return index - startIndex;
}

void Parser::HandleOperation(Token* newToken) {
  size_t nameLength = _findNameLength(expr, curIndex);
  std::string name = expr.substr(curIndex, nameLength);
  auto fIt = loader.GetFuncs().find(name);
  auto bIt = loader.GetBinOps().find(name);
  auto uIt = loader.GetUnOps().find(name);

  if (fIt != loader.GetFuncs().end()) {
    if (bIt == loader.GetBinOps().end() && uIt == loader.GetUnOps().end()) {
      newToken->type = Token::Type::FUNCTION;
      newToken->val = fIt->second;
    }
    else
      throw std::exception(("Ambigious operation " + name).c_str());
  }
  else if (uIt != loader.GetUnOps().end()) {
    if (bIt == loader.GetBinOps().end()) {
      newToken->type = Token::Type::UN_OPERATOR;
      newToken->val = uIt->second;
    }
    else {
      if (!tokens.empty() && (
        tokens.back()->type == Token::Type::NUMBER ||
        tokens.back()->type == Token::Type::FUNCTION ||
        tokens.back()->type == Token::Type::CLS_BRACKET)) {
        newToken->type = Token::Type::BIN_OPERATOR;
        newToken->val = bIt->second;
      }
      else {
        newToken->type = Token::Type::UN_OPERATOR;
        newToken->val = uIt->second;
      }
    }
  }
  else if (bIt != loader.GetBinOps().end()) {
    newToken->type = Token::Type::BIN_OPERATOR;
    newToken->val = bIt->second;
  }
  else
    throw std::exception(("Operation \"" + name + "\" not found").c_str());

  curIndex += nameLength;
}

/**
 * Function for getting tokens (works like output iterator)
 * @return next token
 */
Token* Parser::GetNextToken() {
  SkipSpaces();
  assert(curIndex < expr.length());

  char curSym = expr[curIndex];
  Token* newToken = new Token();
  if (curSym == '(') {
    newToken->type = Token::Type::OPN_BRACKET;
    ++curIndex;
  }
  else if (curSym == ')') {
    newToken->type = Token::Type::CLS_BRACKET;
    ++curIndex;
  }
  else if (isdigit(expr[curIndex])) {
    try {
      HandleNumber(newToken);
    }
    catch (std::exception&) {
      delete newToken;
      throw;
    }
  }
  else {
    HandleOperation(newToken);
  }
  SkipSpaces();
  if (curIndex == expr.length())
    end = true;

  tokens.push_back(newToken);
  return tokens.back();
}

/**
 * End of tokens flag
 * @return true if there are no more tokens else false
 */
bool Parser::IsEnd() const noexcept{
  return end;
}

/**
 * Destructor
 */
Parser::~Parser() {
  for (Token* t : tokens)
    delete t;
}
