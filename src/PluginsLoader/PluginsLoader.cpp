/**
 * @file
 * @brief PluginsLoader source file
 * @authors Pavlov Ilya
 *
 * Contains PluginsLoader and OperationsRegistrar definitions
 */

#include "../include/PluginsLoader.h"
#include <filesystem>

PluginsLoader::PluginsLoader() : opReg (*this) {};

/**
 * Load dllls from directory
 * @param[in] dir relative path to directory
 */
void PluginsLoader::ScanDirectory(const std::string& dir) {
  for (auto& file : std::filesystem::directory_iterator(std::filesystem::current_path().string() + "\\" + dir)) {
    if (file.path().extension() == ".dll") {
      auto dll = LoadLibrary(file.path().string().c_str());
      if (dll) {
        on_load_t on_load = (on_load_t)GetProcAddress(dll, "on_load");
        if (on_load) {
          plugins.push_back(dll);
          on_load(opReg);
        }
        else {
          FreeLibrary(dll);
        }
      }
    }
  }
}

/**
 * Get map of loaded functions
 * @return map of loaded functions
 */
const std::unordered_map<std::string, IFunction*>& PluginsLoader::GetFuncs() const noexcept {
  return funcs;
}

/**
 * Get map of loaded binary operators
 * @return map of loaded operators
 */
const std::unordered_map<std::string, IBinaryOperator*>& PluginsLoader::GetBinOps() const noexcept {
  return binOps;
}

/**
 * Get map of loaded unary functions
 * @return map of loaded operators
 */
const std::unordered_map<std::string, IUnaryOperator*>& PluginsLoader::GetUnOps() const noexcept {
  return unaryOps;
}

/**
 * Clear maps and free loaded libraries
 */
void PluginsLoader::Clear() {
  for (auto& dll : plugins)
    FreeLibrary(dll);

  for (auto f : funcs)
    delete f.second;

  for (auto op : binOps)
    delete op.second;

  for (auto op : unaryOps)
    delete op.second;

  plugins.clear();
}

PluginsLoader::~PluginsLoader() {
  Clear();
}

OperationsRegistrar::OperationsRegistrar(PluginsLoader& loader) : loader(loader) {};

/**
 * Add function to calculator
 * @param[in] f function to add
 */
void OperationsRegistrar::AddFunction(IFunction* f) const {
  loader.funcs.insert_or_assign(f->Name(), f);
}

/**
 * Add binary operator to calculator
 * @param[in] op operator to add
 */
void OperationsRegistrar::AddBinaryOperator(IBinaryOperator* op) const {
  loader.binOps.insert_or_assign(op->Name(), op);
}

/**
 * Add unary operator to calculator
 * @param[in] op operator to add
 */
void OperationsRegistrar::AddUnaryOperator(IUnaryOperator* op) const {
  loader.unaryOps.insert_or_assign(op->Name(), op);
}
