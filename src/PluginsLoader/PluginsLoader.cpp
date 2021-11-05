#include "../include/PluginsLoader.h"
#include <filesystem>

PluginsLoader::PluginsLoader() : opReg (*this) {};

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

const std::unordered_map<std::string, IFunction*>& PluginsLoader::GetFuncs() const noexcept {
  return funcs;
}

const std::unordered_map<std::string, IBinaryOperator*>& PluginsLoader::GetBinOps() const noexcept {
  return binOps;
}

const std::unordered_map<std::string, IUnaryOperator*>& PluginsLoader::GetUnOps() const noexcept {
  return unaryOps;
}

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

void OperationsRegistrar::AddFunction(IFunction* f) const {
  loader.funcs.insert_or_assign(f->Name(), f);
}

void OperationsRegistrar::AddBinaryOperator(IBinaryOperator* op) const {
  loader.binOps.insert_or_assign(op->Name(), op);
}

void OperationsRegistrar::AddUnaryOperator(IUnaryOperator* op) const {
  loader.unaryOps.insert_or_assign(op->Name(), op);
}
