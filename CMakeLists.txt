cmake_minimum_required(VERSION 3.10)

project(AlgorithmicImplementation VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Indicar a CMake dónde buscar los archivos de cabecera (.hpp)
include_directories(include)

# 2. Buscar automáticamente todos los archivos .cpp y .hpp en las carpetas src e include
file(GLOB_RECURSE FUENTES 
    "src/*.cpp"
    "include/*.hpp"
)

# 3. Definir el ejecutable usando la lista automática de fuentes
add_executable(Algorithms ${FUENTES})