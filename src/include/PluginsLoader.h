#pragma once

#include <string>
#include <unordered_map>
#include <Windows.h>
#include "IFunction.h"
#include "IOperator.h"

class PluginsLoader;

class OperationsRegistrar {
private:
  PluginsLoader& loader;
public:
  OperationsRegistrar(PluginsLoader&);
  virtual void AddFunction(IFunction*) const;
  virtual void AddBinaryOperator(IBinaryOperator*) const;
  virtual void AddUnaryOperator(IUnaryOperator*) const;
};

class PluginsLoader {
  friend OperationsRegistrar;
private:
  std::vector<HMODULE> plugins;
  std::unordered_map<std::string, IFunction*> funcs;
  std::unordered_map<std::string, IBinaryOperator*> binOps;
  std::unordered_map<std::string, IUnaryOperator*> unaryOps;
  const OperationsRegistrar opReg;
public:
  using on_load_t = void (*)(const OperationsRegistrar&);

  PluginsLoader();
  void ScanDirectory(const std::string&);
  const std::unordered_map<std::string, IFunction*>& GetFuncs() const noexcept;
  const std::unordered_map<std::string, IBinaryOperator*>& GetBinOps() const noexcept;
  const std::unordered_map<std::string, IUnaryOperator*>& GetUnOps() const noexcept;
  void Clear();
  ~PluginsLoader();
};