#include "algoritmos.hpp"
#include "funciones.hpp"
// #include <cstring>
// #include <fstream>
// #include <iostream>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <string>

namespace py = pybind11;

// std::map<std::string double> ejecutarAlg (){
//
// }

std::map<std::string, std::vector<double>>
simulate(int algoritmo_id, int problema_id, algo::AlgContext contexto) {

  std::map<std::string, std::vector<double>> res;

  // contexto.max_generations = 300;
  // contexto.max_iter = 100000;
  // contexto.mutation_rate = 0.05;
  // contexto.pop_size = 300;
  // contexto.radio = .6;
  // contexto.tasa_reduccion = 0.8;
  // contexto.alpha = 0.99;
  // contexto.n_tweaks_sample = 10;
  // contexto.max_list_tabu = 20;
  meta::Resultado resultado = algo::lista_algoritmos[algoritmo_id].algoritmo(
      prob::lista_problemas[problema_id], contexto);
  // std::cout << "Problema finalizado" << std::endl;
  // hola este es un comentario de prueba
  // std::ofstream archivo("resultados.csv");
  //
  // if (!archivo.is_open()) {
  //   std::cerr << "Error al abrir el archivo" << std::endl;
  // }
  // archivo << "#" << "Algoritmo: " <<
  // algo::lista_algoritmos[algoritmo_id].name
  //         << ", Problema: " << prob::lista_problemas[problema_id].name
  //         << std::endl;
  //
  // archivo << "tiempo" << "," << "best_score" << "," << "best_position_x"
  //         << "," << "best_position_y" << std::endl;
  for (int i = 0; i < resultado.Historial.size(); i++) {
    res["tiempo"].push_back(resultado.Historial[i].t);
    res["best_score"].push_back(resultado.Historial[i].mejor_valor);
    res["best_x"].push_back(resultado.Historial[i].mejor_x);
    res["best_y"].push_back(resultado.Historial[i].mejor_y);

    // archivo << resultado.Historial[i].t << ","
    //         << resultado.Historial[i].mejor_valor << ","
    //         << resultado.Historial[i].mejor_x << ", "
    //         << resultado.Historial[i].mejor_y << std::endl;
  }
  return res;
}

std::map<std::string, std::vector<double>> map_problem(int problema_id,
                                                       int definicion) {

  std::map<std::string, std::vector<double>> res;
  for (double i = 0; i <= definicion; i++) {
    for (double j = 0; j <= definicion; j++) {

      double x = (prob::lista_problemas[problema_id].limit_x.min +
                  i *
                      (prob::lista_problemas[problema_id].limit_x.max -
                       prob::lista_problemas[problema_id].limit_x.min) /
                      definicion);
      double y = (prob::lista_problemas[problema_id].limit_y.min +
                  j *
                      (prob::lista_problemas[problema_id].limit_y.max -
                       prob::lista_problemas[problema_id].limit_y.min) /
                      definicion);

      res["x"].push_back(x);
      res["y"].push_back(y);
      res["f"].push_back(prob::lista_problemas[problema_id].evaluar(x, y));
      // archivo << x << "," << y << ","
      //         << prob::lista_problemas[problema_id].evaluar(x, y)
      //         << std::endl;
    }
  }
  return res;
}

py::dict lista() {
  py::dict d;
  // d["algoritmos"]=std::vector<py::dict>();
  // d["funciones"]=std::vector<py::dict>();
  std::vector<py::dict> algoritmos;
  std::vector<py::dict> funciones;

  // d["algoritmos"]

  for (int i = 0; i < algo::lista_algoritmos.size(); i++) {
    algo::AlgoritmoOptimizacion algoritmo = algo::lista_algoritmos[i];
    py::dict algo;
    algo["name"] = algoritmo.name;
    algo["contexto"] = algoritmo.context_parameter_names;
    algoritmos.push_back(algo);
  };

  for (int i = 0; i < prob::lista_problemas.size(); i++) {
    prob::Optimization_Problem problema = prob::lista_problemas[i];
    py::dict func;
    func["name"] = problema.name;
    func["limit_x_min"] = problema.limit_x.min;
    func["limit_x_max"] = problema.limit_x.max;
    func["limit_y_min"] = problema.limit_y.min;
    func["limit_y_max"] = problema.limit_y.max;
    // algo["name"] = algoritmo.name;
    // algo["contexto"] = algoritmo.context_parameter_names;
    funciones.push_back(func);
  };
  d["algoritmos"] = algoritmos;
  d["funciones"] = funciones;
  return d;
}

PYBIND11_MODULE(Algorithms, m) {
  m.doc() =
      "Módulo para resolver problemas de optimización con Metaheurísticas.";

  // contexto.max_generations = 300;
  // contexto.max_iter = 100000;
  // contexto.mutation_rate = 0.05;
  // contexto.pop_size = 300;
  // contexto.radio = .6;
  // contexto.tasa_reduccion = 0.8;
  // contexto.alpha = 0.99;
  // contexto.n_tweaks_sample = 10;
  // contexto.max_list_tabu = 20;
  py::class_<algo::AlgContext>(m, "contextoAlg")
      .def(py::init<>())
      .def_readwrite("max_generations", &algo::AlgContext::max_generations)
      .def_readwrite("max_iter", &algo::AlgContext::max_iter)
      .def_readwrite("mutation_rate", &algo::AlgContext::mutation_rate)
      .def_readwrite("pop_size", &algo::AlgContext::pop_size)
      .def_readwrite("radio", &algo::AlgContext::radio)
      .def_readwrite("tasa_reduccion", &algo::AlgContext::tasa_reduccion)
      .def_readwrite("alpha", &algo::AlgContext::alpha)
      .def_readwrite("n_tweaks_sample", &algo::AlgContext::n_tweaks_sample)
      .def_readwrite("max_list_tabu", &algo::AlgContext::max_list_tabu);
  m.def("simular", &simulate,
        "Simula la solución de un problema de optimización con cierta "
        "metaheurística.",
        py::arg("algoritmo_id"), py::arg("problema_id"), py::arg("contexto"));
  m.def("map_problema", &map_problem,
        "Dibuja la silueta de la funcion objetivo en sus límites",
        py::arg("problema_id"), py::arg("definicion"));
  // m.def("generar_numeros", &generar_numeros, py::arg("n"));
  // m.def("calcular_estadisticas", &calcular_estadisticas, py::arg("datos"));
  // m.def("agrupar_pares_impares", &agrupar_pares_impares, py::arg("numeros"));
  m.def("lista", &lista);
}

// int main(int argc, char *argv[]) {
//   if (std::strcmp(argv[1], "-s") == 0) {
//     std::ofstream archivo("image_funcion.csv");
//     if (!archivo.is_open()) {
//       std::cerr << "Error al abrir el archivo" << std::endl;
//     }
//     archivo << "x,y,f" << std::endl;
//     int problema_id = std::stoi(argv[2]);
//
//     for (double i = 0; i <= std::stoi(argv[3]); i++) {
//       for (double j = 0; j <= std::stoi(argv[3]); j++) {
//
//         double x = (prob::lista_problemas[problema_id].limit_x.min +
//                     i *
//                         (prob::lista_problemas[problema_id].limit_x.max -
//                          prob::lista_problemas[problema_id].limit_x.min) /
//                         std::stoi(argv[3]));
//         double y = (prob::lista_problemas[problema_id].limit_y.min +
//                     j *
//                         (prob::lista_problemas[problema_id].limit_y.max -
//                          prob::lista_problemas[problema_id].limit_y.min) /
//                         std::stoi(argv[3]));
//
//         archivo << x << "," << y << ","
//                 << prob::lista_problemas[problema_id].evaluar(x, y)
//                 << std::endl;
//       }
//     }
//     return 0;
//   }
//   if (strcmp(argv[1], "-l") == 0) {
//     std::ofstream archivo("lista.json");
//
//     if (!archivo.is_open()) {
//       std::cerr << "Error al abrir el archivo" << std::endl;
//     }
//
//     archivo << "{\"algoritmos\":[";
//
//     for (int i = 0; i < algo::lista_algoritmos.size(); i++) {
//       algo::AlgoritmoOptimizacion algoritmo = algo::lista_algoritmos[i];
//       archivo << "{";
//       archivo << " \"name\": \"" << algoritmo.name << "\",";
//       archivo << " \"contexto\":[";
//       for (int j = 0; j < algoritmo.context_parameter_names.size(); j++) {
//         if (j == algoritmo.context_parameter_names.size() - 1) {
//           archivo << "\"" << algoritmo.context_parameter_names[i] << "\"";
//         } else {
//           archivo << "\"" << algoritmo.context_parameter_names[i] << "\",";
//         }
//       }
//       archivo << "],";
//       if (i == algo::lista_algoritmos.size() - 1) {
//         archivo << "\"id\":" << i << "}";
//       } else {
//         archivo << " \"id\":" << i << "},";
//       }
//     };
//
//     archivo << "], \"funciones\":[";
//
//     for (int i = 0; i < prob::lista_problemas.size(); i++) {
//       prob::Optimization_Problem problema = prob::lista_problemas[i];
//       archivo << "{";
//       archivo << "  \"name\":\"" << problema.name;
//       archivo << "\", \"limit_x_min\":" << problema.limit_x.min;
//       archivo << ", \"limit_x_max\":" << problema.limit_x.max;
//       archivo << ", \"limit_y_min\":" << problema.limit_y.min;
//       archivo << ", \"limit_y_max\": " << problema.limit_y.max;
//       if (i == prob::lista_problemas.size() - 1) {
//         archivo << "}";
//       } else {
//         archivo << "},";
//       }
//     };
//
//     archivo << "]}";
//
//     return 0;
//   }
//   int problema_id = std::stoi(argv[1]);
//   int algoritmo_id = std::stoi(argv[2]);
//
//   // std::cout << "Cargando Problema" << std::endl;
//   algo::AlgContext contexto;
//   contexto.max_generations = 300;
//   contexto.max_iter = 100000;
//   contexto.mutation_rate = 0.05;
//   contexto.pop_size = 300;
//   contexto.radio = .6;
//   contexto.tasa_reduccion = 0.8;
//   contexto.alpha = 0.99;
//   contexto.n_tweaks_sample = 10;
//   contexto.max_list_tabu = 20;
//   meta::Resultado resultado = algo::lista_algoritmos[algoritmo_id].algoritmo(
//       prob::lista_problemas[problema_id], contexto);
//   // std::cout << "Problema finalizado" << std::endl;
//   // hola este es un comentario de prueba
//   std::ofstream archivo("resultados.csv");
//
//   if (!archivo.is_open()) {
//     std::cerr << "Error al abrir el archivo" << std::endl;
//   }
//   archivo << "#" << "Algoritmo: " <<
//   algo::lista_algoritmos[algoritmo_id].name
//           << ", Problema: " << prob::lista_problemas[problema_id].name
//           << std::endl;
//
//   archivo << "tiempo" << "," << "best_score" << "," << "best_position_x"
//           << "," << "best_position_y" << std::endl;
//   for (int i = 0; i < resultado.Historial.size(); i++) {
//     archivo << resultado.Historial[i].t << ","
//             << resultado.Historial[i].mejor_valor << ","
//             << resultado.Historial[i].mejor_x << ", "
//             << resultado.Historial[i].mejor_y << std::endl;
//   }
//   // std::cout << "Problema: " << prob::lista_problemas[problema_id].name
//   // << std::endl;
//
//   return 0;
// }
