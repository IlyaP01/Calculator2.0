cmake_minimum_required (VERSION 3.8)


project(Plugins)

add_library(Core SHARED Core/Core.h Core/Core.cpp)
add_library(Pow SHARED Pow/Pow.h Pow/Pow.cpp)
add_library(Max SHARED Max/Max.h Max/Max.cpp)
add_library(Trig SHARED Trig/Trig.h Trig/Trig.cpp)