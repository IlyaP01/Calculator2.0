#include "Calculator.h"
#include "../Parser/Parser.h"
#include <stack>
#include <cassert>
#include <vector>
#include <typeinfo>

static IFunction* _getFunc(const Token* token) {
  assert(token->type == Token::Type::FUNCTION);
  return dynamic_cast<IFunction*>(std::get<IOperation*>(token->val));
}

static IBinaryOperator* _getBinary(const Token* token) {
  assert(token->type == Token::Type::BIN_OPERATOR);
  return dynamic_cast<IBinaryOperator*>(std::get<IOperation*>(token->val));
}

static IUnaryOperator* _getUnary(const Token* token) {
  assert(token->type == Token::Type::UN_OPERATOR);
  return dynamic_cast<IUnaryOperator*>(std::get<IOperation*>(token->val));
}

static double _calcFunc(const IFunction* func, std::stack<double>& numStack) {
  int numOFParams = func->NumOfParams();
  std::vector<double> args(numOFParams);

  if (numStack.size() < numOFParams) {
    std::string msg = std::string("Wrong number of arguments in function ") + func->Name();
    throw std::exception(msg.c_str());
  }
  for (int i = 0; i < numOFParams; ++i) {
    args.push_back(numStack.top());
    numStack.pop();
  }
  
  std::reverse(args.begin(), args.end());
  return (*func)(args);
}

static double _calcUnary(const IUnaryOperator* op, std::stack<double>& numStack) {
  if (numStack.empty()) {
    std::string msg = std::string("Wrong number of arguments for operator ") + op->Name();
    throw std::exception(msg.c_str());
  }

  double arg = numStack.top();
  numStack.pop();

  return (*op)(arg);
}

static double _calcBinary(const IBinaryOperator* op, std::stack<double>& numStack) {
  if (numStack.size() < 2) {
    std::string msg = std::string("Wrong number of arguments for operator ") + op->Name();
    throw std::exception(msg.c_str());
  }

  double arg2 = numStack.top();
  numStack.pop();
  double arg1 = numStack.top();
  numStack.pop();

  return (*op)(arg1, arg2);
}

static void _calcOperation(const Token* opToken, std::stack<double>& numStack) {
  try {
    if (opToken->type == Token::Type::FUNCTION)
      numStack.push(_calcFunc(_getFunc(opToken), numStack));
    else if (opToken->type == Token::Type::BIN_OPERATOR)
      numStack.push(_calcBinary(_getBinary(opToken), numStack));
    else if (opToken->type == Token::Type::UN_OPERATOR)
      numStack.push(_calcUnary(_getUnary(opToken), numStack));
  }
  catch (...) {
    throw;
  }
}

static void _recalcStacksToOpnBracket(std::stack<Token*>& opStack, std::stack<double>& numStack) {
  while (!opStack.empty() && opStack.top()->type != Token::Type::OPN_BRACKET) {
    try {
      _calcOperation(opStack.top(), numStack);
      opStack.pop();
    }
    catch (std::exception&) {
      throw;
    }
  }

  if (opStack.empty()) {
    throw std::exception("Missing open bracket");
  }

}

static int _comparePriority(const Token* t1, const Token* t2) {
  if (t1->type == Token::Type::FUNCTION)
    return 1;
  if (t1->type == Token::Type::OPN_BRACKET)
    return -1;
  if (t1->type == Token::Type::UN_OPERATOR) {
    auto op = _getUnary(t1);
    return op->GetAffixType() == IUnaryOperator::AffixType::POSTFIX ? -1 : 1;
  }
  if (t2->type == Token::Type::UN_OPERATOR) {
    auto op = _getUnary(t2);
    return op->GetAffixType() == IUnaryOperator::AffixType::POSTFIX ? 1 : -1;
  }
  if (t1->type == Token::Type::BIN_OPERATOR && t2->type == Token::Type::BIN_OPERATOR) {
    auto op1 = dynamic_cast<IBinaryOperator*>(std::get<IOperation*>(t1->val));
    auto op2 = dynamic_cast<IBinaryOperator*>(std::get<IOperation*>(t2->val));
    if (op1->Priority() > op2->Priority())
      return 1;
    else if (op1->Priority() == op2->Priority())
      return op2->GetAssocType() == IBinaryOperator::AssocType::LEFT;
    else
      return -1;
  }

  return -1;
}

Calculator::Calculator() {
  loader.ScanDirectory("plugins");
}

double Calculator::Calculate(const std::string& expression) {
  Parser parser(expression, loader);
  std::stack<Token*> opStack;
  std::stack<double> numStack;
  try {
    while (!parser.IsEnd()) {
      Token* token = parser.GetNextToken();
      switch (token->type) {
      case Token::Type::NUMBER:
        numStack.push(std::get<double>(token->val));
        break;
      case Token::Type::OPN_BRACKET:
      case Token::Type::FUNCTION:
        opStack.push(token);
        break;
      case Token::Type::CLS_BRACKET:
        _recalcStacksToOpnBracket(opStack, numStack);
        opStack.pop();
        if (!opStack.empty() && opStack.top()->type == Token::Type::FUNCTION) {
          auto func = _getFunc(opStack.top());
          numStack.push(_calcFunc(func, numStack));
          opStack.pop();
        }
        break;
      case Token::Type::UN_OPERATOR:
      case Token::Type::BIN_OPERATOR:
        while (!opStack.empty() && _comparePriority(opStack.top(), token) > 0) {
          _calcOperation(opStack.top(), numStack);
          opStack.pop();
        }
        if (token->type == Token::Type::UN_OPERATOR) {
          auto op = _getUnary(token);
          if (op->GetAffixType() == IUnaryOperator::AffixType::POSTFIX)
            numStack.push(_calcUnary(op, numStack));
        }
        else
          opStack.push(token);
        break;
      }
    }

    while (!opStack.empty()) {
      if (opStack.top()->type == Token::Type::OPN_BRACKET)
        throw std::exception("Missing close bracket");
      else {
        _calcOperation(opStack.top(), numStack);
        opStack.pop();
      }
    }

    if (numStack.size() != 1 || !opStack.empty())
      throw std::exception("Invalid expression");
  }
  catch (std::bad_alloc&) {
    throw std::exception("Error allocating memory");
  }
  catch (std::bad_cast&) { // must not be, if program was written right
    throw std::exception("Something wrong");
    assert(false);
  }
  catch (std::bad_variant_access&) { // must not be, if program was written right
    throw std::exception("Something wrong");
    assert(false);
  }
  catch (std::exception&) {
    throw;
  }

  return numStack.top();
}
