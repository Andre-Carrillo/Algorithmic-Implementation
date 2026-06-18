#include "algoritmos.hpp"
#include "meta.hpp"
#include <vector>
#include <random>

static std::mt19937 motor(42);

//Parametros ocultos

//Genetic algorithm
int tournament_size = 4; //Tamaño del torneo para el algoritmo de seleccion para el cruce


meta::Resultado algo::PM_Genetic_Algorithm(const std::function<double(const std::vector<double>&)>& funcion_optimizar,
                                        int pop_size, 
                                        double mutation_rate,
                                        double limits[2][2],
                                        int max_generations){

    struct individuo{
        std::vector<double> xy;
        double score;
        void evaluate(const std::function<double(const std::vector<double>&)>& funcion_optimizar){
            score = funcion_optimizar(xy);
        };
    };

    std::uniform_real_distribution<double> x_range(limits[0][0], limits[0][1]);
    std::uniform_real_distribution<double> y_range(limits[1][0], limits[1][1]);

    std::vector<individuo> poblacion;
    for(int i=0; i<pop_size;i++){
        std::vector<double> xy = {x_range(motor), y_range(motor)};
        individuo i_individuo={xy,0.0};
        poblacion.push_back(i_individuo);
    }

    individuo mejor{};

    //para la selección
    std::uniform_int_distribution<int> indice_random(0, pop_size-1);

    auto seleccion = [&poblacion, &indice_random]() -> individuo{
        std::vector<individuo> participantes;
        individuo mejor{};
        for(int i=0; i<tournament_size; i++){
            participantes.push_back(poblacion[indice_random(motor)]);
            if(participantes[i].score > mejor.score){
                mejor = participantes[i];
            }
        }
        return mejor;
    };

    //crossover

    //mutate
    

    for (int i=0; i<max_generations; i++){
        for(individuo& ind : poblacion){
            ind.evaluate(funcion_optimizar);
            if (mejor.score<ind.score){
                mejor = ind;
            }
        }
        std::vector<individuo> new_pop{};

        for (int j=0; j<pop_size; j++){
            individuo p1 = seleccion();
            individuo p2 = seleccion();

            std::vector<double> hijo_pos = {(p1.xy[0]+p2.xy[0])/2, (p1.xy[1]+p2.xy[1])/2};
            individuo hijo = {hijo_pos, 0.0};
            

        }


    }



}