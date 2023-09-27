#pragma once

#include "modelo/modelo.h"
#include <SFML/Audio.hpp>

#define MAXIMO_PIZZAS_EN_PREPARACION 3
#define MAXIMO_PIZZAS_PREPARADAS 4

namespace tiempos {
    const auto RETARDO_ANTES_DE_RESULTADO = Tiempo::desde_segundos(2.5);
    const auto ESPERA_ENTRE_NIVELES = Tiempo::desde_segundos(2);
} // namespace tiempos

struct Globales {
    sf::RenderWindow window;
    sf::Font font;
    std::optional<sf::SoundBuffer> success_buffer;
    std::optional<sf::SoundBuffer> button_click_buffer;
    sf::Music music;
};

enum class FaseNivel {
    MostrandoInstrucciones,
    Activa,
    EsperaAntesDeResultado,
    MostrandoResultado,
    Reiniciando,
    Saliendo
};

struct Estado {
    FaseNivel fase_actual = FaseNivel::MostrandoInstrucciones;
    PizzasAContadores contadores;
    std::vector<EncargoACocina> encargadas;
};

// Datos para un nivel determinado de un tipo concreto de pizza
struct DatosNivelTipoPizza {
    TipoPizza tipo;
    int pizzas_preparadas_iniciales = 0;
    int objetivo_pizzas = 0;
};

struct PedidosEstaticos {
    std::map<TipoPizza, DatosNivelTipoPizza> pizzas;
};

struct DatosNivel {
    std::string instrucciones;
    PedidosEstaticos pedidos;
    DatosNivel(std::string instr, PedidosEstaticos pizzas)
        : instrucciones(instr), pedidos(pizzas) {}
};
