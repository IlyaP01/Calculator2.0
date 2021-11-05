cmake_minimum_required (VERSION 3.8)

project ("Calculator")

set(CALC_SOURCE src/Calculator/Calculator.cpp 
				src/Calculator/Calculator.h 
				src/Parser/Parser.cpp 
				src/Parser/Parser.h 
				src/PluginsLoader/PluginsLoader.cpp
				src/include/IOperation.h 
				src/include/PluginsLoader.h
				src/include/IFunction.h 
				src/include/IOperator.h 
				src/main.cpp )

add_executable (Calculator ${CALC_SOURCE})

set_property(TARGET Calculator PROPERTY CXX_STANDARD 17)

add_subdirectory(src/DLLs plugins)
