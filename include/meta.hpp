#pragma once
#include <vector>
#include <string>
//Lista de algoritmos que serán puestos a prueba para la optimización

namespace meta{

    struct PuntoHistorial{
        double t;
        int iteracion;
        double mejor_valor;
    };

    // struct Metadatos{
    //     int generaciones_totales;
    //     int evaluaciones_funcion;
    //     std::string razon_parada; //si fue por convergencia, o max_iter
    // };

    struct Resultado{
        std::vector<PuntoHistorial> Historial;
        //Metadatos metadata;
    };

}