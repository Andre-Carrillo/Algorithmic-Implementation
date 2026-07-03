#include "algoritmos.hpp"
#include "funciones.hpp"
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
  int problema_id = std::stoi(argv[1]);
  int algoritmo_id = std::stoi(argv[2]);

  std::cout << "Cargando Problema" << std::endl;
  algo::AlgContext contexto;
  contexto.max_generations = 300;
  contexto.max_iter = 1000;
  contexto.mutation_rate = 0.05;
  contexto.pop_size = 300;
  contexto.radio = 0.5;
  meta::Resultado resultado = algo::lista_algoritmos[algoritmo_id](
      prob::lista_problemas[problema_id], contexto);
  std::cout << "Problema finalizado" << std::endl;
  // hola este es un comentario de prueba

  for (int i = 0; i < resultado.Historial.size(); i++) {
    std::cout << "Tiempo: " << resultado.Historial[i].t
              << "|   Best_score: " << resultado.Historial[i].mejor_valor
              << "|  Mejor posicion: " << resultado.Historial[i].mejor_x << ", "
              << resultado.Historial[i].mejor_y << std::endl;
  }
  std::cout << "Problema: " << prob::lista_problemas[problema_id].name
            << std::endl;

  return 0;
}
