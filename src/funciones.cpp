#include "funciones.hpp"
#include <cmath>

prob::Optimization_Problem iniciarEsfera(){
    prob::Optimization_Problem esfera;
    esfera.name = "Esfera de De Jong";
    esfera.limit_x = {-5,5};
    esfera.limit_y = {-5,5};
    esfera.funcion_costo = [](const std::vector<double>& v){
        return (v[0]*v[0]+v[1]*v[1]);
    };
    return esfera;
}

prob::Optimization_Problem iniciarHimmelblau(){
    prob::Optimization_Problem HimmelBlau;
    HimmelBlau.name = "Problema de HimmelBlau";
    HimmelBlau.limit_x = {-4,4};
    HimmelBlau.limit_y = {-4,4};
    HimmelBlau.funcion_costo = [](const std::vector<double>& v){
        return (std::pow(v[0]*v[0]+v[1]-11,2)+std::pow(v[0]+v[1]*v[1]-7,2));
    };
    return HimmelBlau;
}