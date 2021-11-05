/**
 * @file
 * @brief PluginsLoader class header file
 * @authors Pavlov Ilya
 *
 * Contains PluginsLoader and OperationsRegistrar declarations
 */

#pragma once

#include <string>
#include <unordered_map>
#include <Windows.h>
#include "IFunction.h"
#include "IOperator.h"

class PluginsLoader;

/**
 * @brief OperationsRegistrar class
 *
 * Used on dll load callbacks to add operations to calculator
 */
class OperationsRegistrar {
private:
  PluginsLoader& loader;
public:
  /**
   * Constructor
   * @param[in] loader ref to loader class
   */
  OperationsRegistrar(PluginsLoader& loader);
  
  /**
   * Add function to calculator
   * @param[in] f function to add
   */
  virtual void AddFunction(IFunction* f) const;

  /**
   * Add binary operator to calculator
   * @param[in] op operator to add
   */
  virtual void AddBinaryOperator(IBinaryOperator* op) const;

  /**
   * Add unary operator to calculator
   * @param[in] op operator to add
   */
  virtual void AddUnaryOperator(IUnaryOperator* op) const;
};

/**
 * @brief PluginsLoader class
 *
 * Load and save operations from dlls
 */
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

  /**
   * Load dllls from directory
   * @param[in] dir relative path to directory
   */
  void ScanDirectory(const std::string& dir);

  /**
   * Get map of loaded functions 
   * @return map of loaded functions
   */
  const std::unordered_map<std::string, IFunction*>& GetFuncs() const noexcept;

  /**
   * Get map of loaded binary operators 
   * @return map of loaded operators
   */
  const std::unordered_map<std::string, IBinaryOperator*>& GetBinOps() const noexcept;

  /**
   * Get map of loaded unary functions 
   * @return map of loaded operators
   */
  const std::unordered_map<std::string, IUnaryOperator*>& GetUnOps() const noexcept;

  /**
   * Clear maps and free loaded libraries 
   */
  void Clear();

  ~PluginsLoader();
};