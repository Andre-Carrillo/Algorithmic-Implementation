#include <iostream>
#include <string>
#include "funciones.hpp"
#include "algoritmos.hpp"


int main(int argc, char* argv[]) {
    int problema_id =  std::stoi(argv[1]);
    int algoritmo_id = std::stoi(argv[2]);

    std::cout<< "Cargando Problema"<<std::endl;
    meta::Resultado resultado = algo::lista_algoritmos[algoritmo_id](
        prob::lista_problemas[problema_id], 
        300, 
        0.05, 
        100
    );
    std::cout<< "Problema finalizado" <<std::endl;

    for(int i = 0; i<resultado.Historial.size(); i++){
        std::cout << "Tiempo: " << resultado.Historial[i].t << "|   Best_score: " << resultado.Historial[i].mejor_valor<<"|  Mejor posicion: "<< resultado.Historial[i].mejor_x<<", "<<resultado.Historial[i].mejor_y<<std::endl;
    }
    std::cout<< "Problema: "<<prob::lista_problemas[problema_id].name<<std::endl;

    return 0;
}