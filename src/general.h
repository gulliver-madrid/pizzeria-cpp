#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

namespace modelo_info {
    const auto MAXIMO_PIZZAS_EN_PREPARACION = 3;
    const auto MAXIMO_PIZZAS_PREPARADAS = 4;
} // namespace modelo_info

enum class FaseNivel {
    MostrandoInstrucciones,
    Activa,
    EsperaAntesDeResultado,
    MostrandoResultado,
    Reiniciando,
    Saliendo
};
