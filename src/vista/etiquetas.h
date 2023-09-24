#pragma once

#include "../modelo/dominio.h"
#include <SFML/Graphics.hpp>

struct EtiquetasContadores {
    std::map<TipoPizza, sf::Text> texto_servidas;
    std::map<TipoPizza, sf::Text> texto_preparadas;
    void setup(sf::Font &font);
};

struct EtiquetasInfo {
    sf::Text instrucciones;
    sf::Text resultado;
};
