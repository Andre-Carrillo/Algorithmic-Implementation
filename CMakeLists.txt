cmake_minimum_required(VERSION 3.10)

project(AlgorithmicImplementation VERSION 1.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# list(APPEND CMAKE_PREFIX_PATH "${Python3_SITELIB}/pybind11/share/cmake/pybind11")
# find_package(pybind11 REQUIRED)
# find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
# set(PYBIND11_FINDPYTHON ON) # Obliga a usar el módulo moderno de Python
# find_package(pybind11 CONFIG REQUIRED)
find_package(pybind11 REQUIRED PATHS "${CMAKE_SOURCE_DIR}/venv/lib64/python3.14/site-packages/pybind11/share/cmake/pybind11")

# 1. Indicar a CMake dónde buscar los archivos de cabecera (.hpp)
include_directories(include)

# 2. Buscar automáticamente todos los archivo
# file(glob_recurse fuentes
#     "src/*.cpp"
#     "include/*.hpp"
#     # "venv/lib64/python3.14/site-packages/pybind11/include/pybind11/pybind11.h"
# )
# file(GLOB_RECURSE SOURCES "src/*.cpp")
# file(GLOB_RECURSE HEADERS "include/*.hpp")
# 3. Definir el ejecutable usando la lista automática de fuentes
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE HEADERS "${CMAKE_SOURCE_DIR}/include/*.hpp")
# pybind11_add_module(Algorithms src/main.cpp ...)

pybind11_add_module(Algorithms ${SOURCES})
target_include_directories(Algorithms PRIVATE "${CMAKE_SOURCE_DIR}/include")
# add_executable(Algorithms ${FUENTES})
# target_link_libraries(Algorithms PRIVATE pybind11::module)
target_include_directories(Algorithms PRIVATE include)
