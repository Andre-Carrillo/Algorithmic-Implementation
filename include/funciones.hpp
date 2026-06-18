#pragma once
#include <string>
#include <functional>

namespace prob{

    struct Limit{
        double min;
        double max;
    };

    struct Optimization_Problem{
        std::string name;
        Limit limit_x;
        Limit limit_y;

        std::function<double(const std::vector<double>&)> funcion_costo;

        double evaluar (double x, double y) const {
            return funcion_costo({x,y});
        }
    };

    //Declaración de problemas de optimización

    Optimization_Problem iniciarEsfera();
    Optimization_Problem iniciarHimmelblau();
}