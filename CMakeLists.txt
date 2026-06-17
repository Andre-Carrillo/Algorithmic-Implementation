# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

# Nombre del proyecto y lenguaje
project(AlgorithmicImpelemtation VERSION 1.0 LANGUAGES CXX)

# Exigir C++17 o superior (puedes cambiarlo a 20 o 23 si lo requieres)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Definir el ejecutable y dónde encontrar las fuentes
add_executable(Algorithms src/main.cpp)