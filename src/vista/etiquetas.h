#pragma once

#include "../modelo/dominio.h"
#include <SFML/Graphics.hpp>

struct EtiquetasContadores {
    std::map<TipoPizza, sf::Text> texto_servidas;
    std::map<TipoPizza, sf::Text> texto_preparadas;
    void setup(sf::Font &font);
    void dibujar(sf::RenderWindow &ventana);
};

struct EtiquetasInfo {
    sf::Text instrucciones;
    sf::Text resultado;
};

sf::Text generar_etiqueta_instrucciones(
    sf::Font &font, std::string plantilla_instrucciones, int objetivo
);
sf::Text generar_etiqueta_resultado(sf::Font &font);
