#include "funciones.hpp"
#include <cmath>
#include <functional>

prob::Optimization_Problem iniciarEsfera() {
  prob::Optimization_Problem esfera;
  esfera.name = "Esfera de De Jong";
  esfera.limit_x = {-5, 5};
  esfera.limit_y = {-5, 5};
  esfera.funcion_costo = [](const std::vector<double> &v) {
    return (v[0] * v[0] + v[1] * v[1]);
  };
  return esfera;
}

prob::Optimization_Problem iniciarHimmelblau() {
  prob::Optimization_Problem HimmelBlau;
  HimmelBlau.name = "Problema de HimmelBlau";
  HimmelBlau.limit_x = {-4, 4};
  HimmelBlau.limit_y = {-4, 4};
  HimmelBlau.funcion_costo = [](const std::vector<double> &v) {
    return (std::pow(v[0] * v[0] + v[1] - 11, 2) +
            std::pow(v[0] + v[1] * v[1] - 7, 2));
  };
  return HimmelBlau;
}

prob::Optimization_Problem iniciarBeale() {
  prob::Optimization_Problem Beale;
  Beale.name = "Problema de Beale";
  Beale.limit_x = {-4.5, 4.5};
  Beale.limit_y = {-4.5, 4.5};
  Beale.funcion_costo = [](const std::vector<double> &v) {
    return (std::pow(1.5 - v[0] * v[0] + v[1] * v[0], 2) +
            std::pow(2.25 - v[0] + v[0] * v[1] * v[1], 2) +
            std::pow(2.625 - v[0] + v[0] * v[1] * v[1] * v[1], 2));
  };
  return Beale;
}

prob::Optimization_Problem iniciarMatyas() {
  prob::Optimization_Problem Matyas;
  Matyas.name = "Problema de Matyas";
  Matyas.limit_x = {-10, 10};
  Matyas.limit_y = {-10, 10};
  Matyas.funcion_costo = [](const std::vector<double> &v) {
    return (0.26 * (v[0] * v[0] + v[1] * v[1] - 0.48 * v[0] * v[1]));
  };
  return Matyas;
}

prob::Optimization_Problem iniciarRosenbrock() {
  prob::Optimization_Problem Rosenbrock;
  Rosenbrock.name = "Problema de Rosenbrock";
  Rosenbrock.limit_x = {-10, 10};
  Rosenbrock.limit_y = {-10, 10};
  Rosenbrock.funcion_costo = [](const std::vector<double> &v) {
    return (std::pow(10 * (v[1] - v[0] * v[0]), 2) + std::pow((1 - v[0]), 2));
  };
  return Rosenbrock;
}

prob::Optimization_Problem iniciarBooth() {
  prob::Optimization_Problem Booth;
  Booth.name = "Problema de Booth";
  Booth.limit_x = {-10, 10};
  Booth.limit_y = {-10, 10};
  Booth.funcion_costo = [](const std::vector<double> &v) {
    return (std::pow((v[0] + 2 * v[1] - 7), 2) +
            std::pow((2 * v[0] + v[1] - 5), 2));
  };
  return Booth;
}

std::vector<prob::Optimization_Problem> prob::lista_problemas = {
    iniciarEsfera(), iniciarHimmelblau(), iniciarBeale(),
    iniciarMatyas(), iniciarRosenbrock(), iniciarBooth()};
