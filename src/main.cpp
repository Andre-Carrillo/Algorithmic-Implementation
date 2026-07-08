#include "algoritmos.hpp"
#include "funciones.hpp"
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
  if (std::strcmp(argv[1], "-s") == 0) {
    std::ofstream archivo("image_funcion.csv");
    if (!archivo.is_open()) {
      std::cerr << "Error al abrir el archivo" << std::endl;
    }
    archivo << "x,y,f" << std::endl;
    int problema_id = std::stoi(argv[2]);

    for (double i = 0; i <= std::stoi(argv[3]); i++) {
      for (double j = 0; j <= std::stoi(argv[3]); j++) {

        double x = (prob::lista_problemas[problema_id].limit_x.min +
                    i *
                        (prob::lista_problemas[problema_id].limit_x.max -
                         prob::lista_problemas[problema_id].limit_x.min) /
                        std::stoi(argv[3]));
        double y = (prob::lista_problemas[problema_id].limit_y.min +
                    j *
                        (prob::lista_problemas[problema_id].limit_y.max -
                         prob::lista_problemas[problema_id].limit_y.min) /
                        std::stoi(argv[3]));

        archivo << x << "," << y << ","
                << prob::lista_problemas[problema_id].evaluar(x, y)
                << std::endl;
      }
    }
    return 0;
  }
  if (strcmp(argv[1], "-l") == 0) {
    std::ofstream archivo("lista.json");

    if (!archivo.is_open()) {
      std::cerr << "Error al abrir el archivo" << std::endl;
    }

    archivo << "{\"algoritmos\":[";

    for (int i = 0; i < algo::lista_algoritmos.size(); i++) {
      algo::AlgoritmoOptimizacion algoritmo = algo::lista_algoritmos[i];
      archivo << "{";
      archivo << " \"name\": \"" << algoritmo.name << "\",";
      archivo << " \"contexto\":[";
      for (int j = 0; j < algoritmo.context_parameter_names.size(); j++) {
        if (j == algoritmo.context_parameter_names.size() - 1) {
          archivo << "\"" << algoritmo.context_parameter_names[i] << "\"";
        } else {
          archivo << "\"" << algoritmo.context_parameter_names[i] << "\",";
        }
      }
      archivo << "],";
      if (i == algo::lista_algoritmos.size() - 1) {
        archivo << "\"id\":" << i << "}";
      } else {
        archivo << " \"id\":" << i << "},";
      }
    };

    archivo << "], \"funciones\":[";

    for (int i = 0; i < prob::lista_problemas.size(); i++) {
      prob::Optimization_Problem problema = prob::lista_problemas[i];
      archivo << "{";
      archivo << "  \"name\":\"" << problema.name;
      archivo << "\", \"limit_x_min\":" << problema.limit_x.min;
      archivo << ", \"limit_x_max\":" << problema.limit_x.max;
      archivo << ", \"limit_y_min\":" << problema.limit_y.min;
      archivo << ", \"limit_y_max\": " << problema.limit_y.max;
      if (i == prob::lista_problemas.size() - 1) {
        archivo << "}";
      } else {
        archivo << "},";
      }
    };

    archivo << "]}";

    return 0;
  }
  int problema_id = std::stoi(argv[1]);
  int algoritmo_id = std::stoi(argv[2]);

  // std::cout << "Cargando Problema" << std::endl;
  algo::AlgContext contexto;
  contexto.max_generations = 300;
  contexto.max_iter = 100000;
  contexto.mutation_rate = 0.05;
  contexto.pop_size = 300;
  contexto.radio = .6;
  contexto.tasa_reduccion = 0.8;
  contexto.alpha = 0.99;
  contexto.n_tweaks_sample = 10;
  contexto.max_list_tabu = 20;
  meta::Resultado resultado = algo::lista_algoritmos[algoritmo_id].algoritmo(
      prob::lista_problemas[problema_id], contexto);
  // std::cout << "Problema finalizado" << std::endl;
  // hola este es un comentario de prueba
  std::ofstream archivo("resultados.csv");

  if (!archivo.is_open()) {
    std::cerr << "Error al abrir el archivo" << std::endl;
  }
  archivo << "#" << "Algoritmo: " << algo::lista_algoritmos[algoritmo_id].name
          << ", Problema: " << prob::lista_problemas[problema_id].name
          << std::endl;

  archivo << "tiempo" << "," << "best_score" << "," << "best_position_x"
          << "," << "best_position_y" << std::endl;
  for (int i = 0; i < resultado.Historial.size(); i++) {
    archivo << resultado.Historial[i].t << ","
            << resultado.Historial[i].mejor_valor << ","
            << resultado.Historial[i].mejor_x << ", "
            << resultado.Historial[i].mejor_y << std::endl;
  }
  // std::cout << "Problema: " << prob::lista_problemas[problema_id].name
  // << std::endl;

  return 0;
}
