#pragma once
#include "meta.hpp"
#include <functional>

namespace algo{
    //meta::Resultado SS_Gradient_Ascent(const std::function<double(const std::vector<double>&)>& funcion_optimizar);
    //meta::Resultado SS_Gradient_Ascent_Restarts(const std::function<double(const std::vector<double>&)>& funcion_optimizar);
    //meta::Resultado SS_HillClimbing(const std::function<double(const std::vector<double>&)>& funcion_optimizar,
                                    // double radio,
                                    // int max_iter,
                                    // double limits[2][2]);
    //meta::Resultado SS_SA_HillClimbing(const std::function<double(const std::vector<double>&)>& funcion_optimizar);
    //meta::Resultado SS_SA_HillClimbing_Replacement(const std::function<double(const std::vector<double>&)>& funcion_optimizar);
    //meta::Resultado SS_HillClimbing_Random_Restart(const std::function<double(const std::vector<double>&)>& funcion_optimizar);

    //meta::Resultado SS_Simmulated_Annealing(const std::function<double(const std::vector<double>&)>& funcion_optimizar, 
                                            // double T_inicial,
                                            // double T_final,
                                            // double alpha,
                                            // double limits[2][2]);
    
    //meta::Resultado SS_Tabu_Search(const std::function<double(const std::vector<double>&)>& funcion_optimizar);
    //meta::Resultado SS_Tabu_Search_FB(const std::function<double(const std::vector<double>&)>& funcion_optimizar);//Feature Based
    //meta::Resultado SS_Iterated_Local_Search_Random_Restart(const std::function<double(const std::vector<double>&)>& funcion_optimizar);
    //meta::Resultado PM_Mu_Lambda(const std::function<double(const std::vector<double>&)>& funcion_optimizar);
    //meta::Resultado PM_Mu_Plus_Lambda(const std::function<double(const std::vector<double>&)>& funcion_optimizar);
    meta::Resultado PM_Genetic_Algorithm(const std::function<double(const std::vector<double>&)>& funcion_optimizar,
                                        int pop_size, 
                                        double mutation_rate,
                                        double limits[2][2],
                                        int max_generations);
}