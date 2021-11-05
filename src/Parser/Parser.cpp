#include "Parser.h"
#include <assert.h>
#include <stdexcept>

Parser::Parser(const std::string& expression, const PluginsLoader& loader) : expr(expression), loader(loader) {}

static void _skipSpaces(const std::string& expr, size_t* index) {
  while (*index < expr.length() && isspace(expr[*index])) {
    ++*index;
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

Token* Parser::GetNextToken() {
  _skipSpaces(expr, &curIndex);
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
      size_t posDiff;
      double val = std::stod(&expr[curIndex], &posDiff);
      newToken->type = Token::Type::NUMBER;
      newToken->val = val;
      curIndex += posDiff;
    }
    catch (std::invalid_argument&){
      delete newToken;
      throw std::exception("invalid number");
    }
    catch (std::out_of_range&) {
      delete newToken;
      throw std::exception("number is too big");
    }
  }
  else {
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
  _skipSpaces(expr, &curIndex);
  if (curIndex == expr.length())
    end = true;

  tokens.push_back(newToken);
  return tokens.back();
}

bool Parser::IsEnd() {
  return end;
}

Parser::~Parser() {
  for (Token* t : tokens)
    delete t;
}
