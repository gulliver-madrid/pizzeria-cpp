#pragma once

#include "cadenas.h"
#include <string>
#include <vector>

struct VistaPreparacionPizza {
    std::string nombre_pizza;
    int porcentaje;
};

struct VistaBarraEstado {
    CadenaJuego texto;
};

struct VistaLinea {
    std::string cadena;
    bool esta_cubierta;
};

struct VistaPedido {
    std::vector<VistaLinea> lineas;
    size_t num_items;
    std::string obtener_cadena_completa() const {
        std::vector<std::string> v;
        for (auto linea : lineas) {
            v.push_back(linea.cadena);
        }
        return unir_cadenas(v, "\n");
    }
};
