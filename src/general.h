#pragma once

#include "modelo/control_pizzas.h"
#include "tiempo.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cassert>
#include <iostream>

#define MAXIMO_PIZZAS_EN_PREPARACION 3
#define MAXIMO_PIZZAS_PREPARADAS 4

namespace tiempos {
    const auto RETARDO_ANTES_DE_RESULTADO = Tiempo::desde_segundos(2.5);
    const auto ESPERA_ENTRE_NIVELES = Tiempo::desde_segundos(2);
} // namespace tiempos

enum class FaseNivel {
    MostrandoInstrucciones,
    Activa,
    EsperaAntesDeResultado,
    MostrandoResultado,
    Reiniciando,
    Saliendo
};

/* Guarda la información relativa al nivel */
struct DatosNivel {
    std::string instrucciones;
    Pedidos pedidos;
    bool es_estatico = false;
};
