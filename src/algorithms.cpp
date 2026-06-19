#include "algoritmos.hpp"
#include "meta.hpp"
#include "funciones.hpp"
#include <vector>
#include <random>
#include <chrono>

static std::mt19937 motor(40);


//Parametros ocultos

//Genetic algorithm
int tournament_size = 4; //Tamaño del torneo para el algoritmo de seleccion para el cruce


meta::Resultado algo::PM_Genetic_Algorithm(prob::Optimization_Problem problema_optimizacion,
                                        int pop_size, 
                                        double mutation_rate,
                                        int max_generations){

    
                                             
    struct individuo{
        std::vector<double> xy;
        double score;
    };

    std::uniform_real_distribution<double> x_range(problema_optimizacion.limit_x.min, problema_optimizacion.limit_x.max);
    std::uniform_real_distribution<double> y_range(problema_optimizacion.limit_y.min, problema_optimizacion.limit_y.max);

    std::vector<individuo> poblacion;
    for(int i=0; i<pop_size;i++){
        std::vector<double> xy = {x_range(motor), y_range(motor)};
        individuo i_individuo={xy,0.0};
        poblacion.push_back(i_individuo);
    }

    individuo mejor=poblacion[0];

    //para la selección
    std::uniform_int_distribution<int> indice_random(0, pop_size-1);

    auto seleccion = [&poblacion, &indice_random, &problema_optimizacion]() -> individuo{
        std::vector<individuo> participantes;
        
        for(int i=0; i<tournament_size; i++){
            participantes.push_back(poblacion[indice_random(motor)]);
            participantes[i].score = problema_optimizacion.evaluar(participantes[i].xy[0], participantes[i].xy[1]);
        }
        individuo mejor = participantes[0];
        mejor.score = problema_optimizacion.evaluar(mejor.xy[0], mejor.xy[1]);
        for(int i=0; i<tournament_size; i++){
            if(participantes[i].score < mejor.score){
                mejor = participantes[i];
            }
        }
        return mejor;
    };
    //mutate
    auto mutate = [mutation_rate](individuo& ind) -> individuo {
        std::uniform_real_distribution<double> d(-0.5, 0.5);
        if ((d(motor) * 2) < mutation_rate) {
            ind.xy = {ind.xy[0] + d(motor), ind.xy[1] + d(motor)};
        }
        return ind; 
    };

    std::vector<meta::PuntoHistorial> Historial{};

    for (int i=0; i<max_generations; i++){
        std::vector<individuo> new_pop = poblacion;
        mejor.score = problema_optimizacion.evaluar(mejor.xy[0], mejor.xy[1]);
        auto iter_start = std::chrono::high_resolution_clock::now();
        for(individuo& ind : new_pop){
            ind.score = problema_optimizacion.evaluar(ind.xy[0], ind.xy[1]);
            if (mejor.score>ind.score){
                mejor = ind;
            }
        }
        

        for (int j=0; j<pop_size; j++){
            individuo p1 = seleccion();
            individuo p2 = seleccion();

            std::vector<double> hijo_pos = {(p1.xy[0]+p2.xy[0])/2, (p1.xy[1]+p2.xy[1])/2};
            individuo hijo = {hijo_pos, 0.0};
            hijo = mutate(hijo);            
            new_pop[j] = hijo;
        }

        poblacion = new_pop;

        auto iter_end = std::chrono::high_resolution_clock::now();
        auto duracion_us = std::chrono::duration_cast<std::chrono::microseconds>(iter_end - iter_start);
        double tiempo_ms = static_cast<double>(duracion_us.count()) / 1000.0;
        meta::PuntoHistorial punto_i = {tiempo_ms, i, mejor.score, mejor.xy[0], mejor.xy[1]};
        Historial.push_back(punto_i);
    }
    meta::Resultado res;
    res.Historial = Historial;
    return res;
}


std::vector<std::function<meta::Resultado(prob::Optimization_Problem, int, double, int)>> algo::lista_algoritmos = {
    algo::PM_Genetic_Algorithm
};