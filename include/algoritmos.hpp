#pragma once
#include "funciones.hpp"
#include "meta.hpp"
#include <functional>

namespace algo {

struct AlgContext {
  int max_iter;
  int pop_size;
  double radio;
  double mutation_rate;
  int max_generations;
};

// este es un comentario
//  meta::Resultado SS_Gradient_Ascent(const prob::Optimization_Problem
//  problema_optimizacion); meta::Resultado SS_Gradient_Ascent_Restarts(const
//  prob::Optimization_Problem problema_optimizacion);
meta::Resultado
SS_HillClimbing(const prob::Optimization_Problem problema_optimizacion,
                AlgContext contexto);
// meta::Resultado SS_SA_HillClimbing(const prob::Optimization_Problem
// problema_optimizacion); meta::Resultado SS_SA_HillClimbing_Replacement(const
// prob::Optimization_Problem problema_optimizacion); meta::Resultado
// SS_HillClimbing_Random_Restart(const prob::Optimization_Problem
// problema_optimizacion);

// meta::Resultado SS_Simmulated_Annealing(const prob::Optimization_Problem
// problema_optimizacion,
//  double T_inicial,
//  double T_final,
//  double alpha,
//  double limits[2][2]);

// meta::Resultado SS_Tabu_Search(const prob::Optimization_Problem
// problema_optimizacion); meta::Resultado SS_Tabu_Search_FB(const
// prob::Optimization_Problem problema_optimizacion);//Feature Based
// meta::Resultado SS_Iterated_Local_Search_Random_Restart(const
// prob::Optimization_Problem problema_optimizacion); meta::Resultado
// PM_Mu_Lambda(const prob::Optimization_Problem problema_optimizacion);
// meta::Resultado PM_Mu_Plus_Lambda(const prob::Optimization_Problem
// problema_optimizacion);
meta::Resultado
PM_Genetic_Algorithm(const prob::Optimization_Problem problema_optimizacion,
                     AlgContext contexto);

extern std::vector<std::function<meta::Resultado(
    const prob::Optimization_Problem, AlgContext)>>
    lista_algoritmos;
} // namespace algo
