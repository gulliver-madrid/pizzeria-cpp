#pragma once

#include "../../shared.h"
#include <SFML/Graphics.hpp>

struct EtiquetasInfo {
    sf::Text instrucciones;
    sf::Text resultado;
};

struct FabricaEtiquetasInfo {
    static sf::Text generar_etiqueta_instrucciones(
        const sf::Font &font,         //
        const std::string &plantilla, //
        NumNivel num_nivel,           //
        int objetivo
    );

    static sf::Text generar_etiqueta_resultado(const sf::Font &font);
};
