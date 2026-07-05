#include "algoritmos.hpp"
#include "funciones.hpp"
#include "meta.hpp"
#include <chrono>
#include <cmath>
#include <random>
#include <vector>

static std::mt19937 motor(40);

// Parametros ocultos

// Genetic algorithm
int tournament_size =
    4; // Tamaño del torneo para el algoritmo de seleccion para el cruce

meta::Resultado
algo::PM_Genetic_Algorithm(prob::Optimization_Problem problema_optimizacion,
                           AlgContext context) {
  int pop_size = context.pop_size;
  double mutation_rate = context.mutation_rate;
  int max_generations = context.max_generations;
  struct individuo {
    std::vector<double> xy;
    double score;
  };

  std::uniform_real_distribution<double> x_range(
      problema_optimizacion.limit_x.min, problema_optimizacion.limit_x.max);
  std::uniform_real_distribution<double> y_range(
      problema_optimizacion.limit_y.min, problema_optimizacion.limit_y.max);

  std::vector<individuo> poblacion;
  for (int i = 0; i < pop_size; i++) {
    std::vector<double> xy = {x_range(motor), y_range(motor)};
    individuo i_individuo = {xy, 0.0};
    poblacion.push_back(i_individuo);
  }

  individuo mejor = poblacion[0];

  // para la selección
  std::uniform_int_distribution<int> indice_random(0, pop_size - 1);

  auto seleccion = [&poblacion, &indice_random,
                    &problema_optimizacion]() -> individuo {
    std::vector<individuo> participantes;

    for (int i = 0; i < tournament_size; i++) {
      participantes.push_back(poblacion[indice_random(motor)]);
      participantes[i].score = problema_optimizacion.evaluar(
          participantes[i].xy[0], participantes[i].xy[1]);
    }
    individuo mejor = participantes[0];
    mejor.score = problema_optimizacion.evaluar(mejor.xy[0], mejor.xy[1]);
    for (int i = 0; i < tournament_size; i++) {
      if (participantes[i].score < mejor.score) {
        mejor = participantes[i];
      }
    }
    return mejor;
  };
  // mutate
  auto mutate = [mutation_rate](individuo &ind) -> individuo {
    std::uniform_real_distribution<double> d(-0.5, 0.5);
    if ((d(motor) * 2) < mutation_rate) {
      ind.xy = {ind.xy[0] + d(motor), ind.xy[1] + d(motor)};
    }
    return ind;
  };

  std::vector<meta::PuntoHistorial> Historial{};
  auto iter_start = std::chrono::high_resolution_clock::now();

  for (int i = 0; i < max_generations; i++) {
    std::vector<individuo> new_pop = poblacion;
    mejor.score = problema_optimizacion.evaluar(mejor.xy[0], mejor.xy[1]);
    for (individuo &ind : new_pop) {
      ind.score = problema_optimizacion.evaluar(ind.xy[0], ind.xy[1]);
      if (mejor.score > ind.score) {
        mejor = ind;
      }
    }

    for (int j = 0; j < pop_size; j++) {
      individuo p1 = seleccion();
      individuo p2 = seleccion();

      std::vector<double> hijo_pos = {(p1.xy[0] + p2.xy[0]) / 2,
                                      (p1.xy[1] + p2.xy[1]) / 2};
      individuo hijo = {hijo_pos, 0.0};
      hijo = mutate(hijo);
      new_pop[j] = hijo;
    }

    poblacion = new_pop;

    auto iter_end = std::chrono::high_resolution_clock::now();
    auto duracion_us = std::chrono::duration_cast<std::chrono::microseconds>(
        iter_end - iter_start);
    double tiempo_ms = static_cast<double>(duracion_us.count()) / 1000.0;
    meta::PuntoHistorial punto_i = {tiempo_ms, i, mejor.score, mejor.xy[0],
                                    mejor.xy[1]};
    Historial.push_back(punto_i);
  }
  meta::Resultado res;
  res.Historial = Historial;
  return res;
}

algo::AlgoritmoOptimizacion algoritmoGenetico = {
    "Algoritmo Genetico",
    {"pop_size", "mutation_rate", "max_generations"},
    algo::PM_Genetic_Algorithm};

meta::Resultado
algo::SS_HillClimbing(const prob::Optimization_Problem problema_optimizacion,
                      AlgContext context) {
  double radio = context.radio;
  double max_iter = context.max_iter;

  std::uniform_real_distribution<double> x_range(
      problema_optimizacion.limit_x.min, problema_optimizacion.limit_x.max);
  std::uniform_real_distribution<double> y_range(
      problema_optimizacion.limit_y.min, problema_optimizacion.limit_y.max);

  std::vector<double> pivot = {x_range(motor), y_range(motor)};

  std::vector<meta::PuntoHistorial> Historial{};

  auto iter_start = std::chrono::high_resolution_clock::now();

  for (int i = 0; i < max_iter; i++) {

    std::uniform_real_distribution<double> x_range_sample(pivot[0] - radio,
                                                          pivot[0] + radio);
    std::uniform_real_distribution<double> y_range_sample(pivot[1] - radio,
                                                          pivot[1] + radio);

    std::vector<double> candidate;
    candidate = {x_range_sample(motor), y_range_sample(motor)};
    if (problema_optimizacion.evaluar(candidate[0], candidate[1]) <
        problema_optimizacion.evaluar(pivot[0], pivot[1])) {
      pivot = candidate;
    }

    auto iter_end = std::chrono::high_resolution_clock::now();
    auto duracion_us = std::chrono::duration_cast<std::chrono::microseconds>(
        iter_end - iter_start);
    double tiempo_ms = static_cast<double>(duracion_us.count()) / 1000.0;
    meta::PuntoHistorial punto_i = {
        tiempo_ms, i, problema_optimizacion.evaluar(pivot[0], pivot[1]),
        pivot[0], pivot[1]};
    Historial.push_back(punto_i);
    radio *= 0.999;
  }
  meta::Resultado res;
  res.Historial = Historial;
  return res;
}

algo::AlgoritmoOptimizacion algoritmoHillClimbing = {
    "Algoritmo Hill Climbing", {"radio", "max_iter"}, algo::SS_HillClimbing};

meta::Resultado algo::SS_Simulated_Annealing(
    const prob::Optimization_Problem problema_optimizacion,
    AlgContext contexto) {
  double r = contexto.tasa_reduccion;
  double a = contexto.alpha;
  double radio = contexto.radio;

  int n_points = 100;
  // Hallar el costo promedio \diff E
  std::vector<std::vector<double>> lista_puntos;
  std::uniform_real_distribution<double> x_range(
      problema_optimizacion.limit_x.min, problema_optimizacion.limit_x.max);
  std::uniform_real_distribution<double> y_range(
      problema_optimizacion.limit_y.min, problema_optimizacion.limit_y.max);

  for (int i = 0; i < n_points; i++) {
    lista_puntos.push_back({x_range(motor), y_range(motor)});
  }
  int count = 0;
  double sum = 0;

  for (int i = 0; i < n_points; i++) {
    for (int j = i; j < n_points; j++) {
      if (problema_optimizacion.evaluar(lista_puntos[i][0],
                                        lista_puntos[i][1]) >
          problema_optimizacion.evaluar(lista_puntos[j][0],
                                        lista_puntos[j][1])) {
        sum += problema_optimizacion.evaluar(lista_puntos[i][0],
                                             lista_puntos[i][1]) -
               problema_optimizacion.evaluar(lista_puntos[j][0],
                                             lista_puntos[j][1]);
        count++;
      }
    }
  }

  double diff_E = sum / count;
  double t = -diff_E / std::log(r);
  // Algoritmo

  std::vector<double> S = {x_range(motor), y_range(motor)};
  std::vector<double> best = S;

  std::vector<meta::PuntoHistorial> Historial{};

  auto iter_start = std::chrono::high_resolution_clock::now();

  int iter = 0;
  while (t > 0.00000001 && iter < contexto.max_iter) {
    std::uniform_real_distribution<double> x_range_sample(S[0] - radio,
                                                          S[0] + radio);
    std::uniform_real_distribution<double> y_range_sample(S[1] - radio,
                                                          S[1] + radio);
    std::vector<double> R = {x_range_sample(motor), y_range_sample(motor)};

    std::uniform_real_distribution<double> zero_one(0, 1);
    if (problema_optimizacion.evaluar(R[0], R[1]) <
            problema_optimizacion.evaluar(S[0], S[1]) ||
        zero_one(motor) < std::exp((problema_optimizacion.evaluar(S[0], S[1]) -
                                    problema_optimizacion.evaluar(R[0], R[1])) /
                                   (t + 1e-9))) {

      S = R;
    }
    t *= a;
    if (problema_optimizacion.evaluar(S[0], S[1]) <
        problema_optimizacion.evaluar(best[0], best[1])) {
      best = S;
    }

    auto iter_end = std::chrono::high_resolution_clock::now();
    auto duracion_us = std::chrono::duration_cast<std::chrono::microseconds>(
        iter_end - iter_start);
    double tiempo_ms = static_cast<double>(duracion_us.count()) / 1000.0;
    meta::PuntoHistorial punto_i = {
        tiempo_ms, iter, problema_optimizacion.evaluar(best[0], best[1]),
        best[0], best[1]};
    Historial.push_back(punto_i);

    iter++;
  }

  meta::Resultado res;
  res.Historial = Historial;
  return res;
}

algo::AlgoritmoOptimizacion algoritmoSimulatedAnnealing = {
    "Algoritmo Simulated Annealing",
    {"radio", "max_iter", "tasa_reduccion", "alpha", "radio"},
    algo::SS_Simulated_Annealing};

// std::vector<std::function<meta::Resultado(prob::Optimization_Problem,
//                                           algo::AlgContext)>>
//     algo::lista_algoritmos = {algo::PM_Genetic_Algorithm,
//                               algo::SS_HillClimbing};
std::vector<algo::AlgoritmoOptimizacion> algo::lista_algoritmos = {
    algoritmoGenetico, algoritmoHillClimbing, algoritmoSimulatedAnnealing};
