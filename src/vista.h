#pragma once

#include "componentes.h"

sf::Text
crearEtiqueta(int tamano, sf::Font &font, sf::Color color = sf::Color::White);
BotonConTexto crearBotonConTexto(
    std::string texto, sf::Color color_fondo, sf::Vector2i posicion,
    sf::Font &font, sf::Color color_texto = sf::Color::White
);
sf::Text crearEtiquetaContador(sf::Font &font);
sf::Text crearEtiquetaPizzasPreparadas(sf::Font &font, float prev_position);

struct Botones {

    BotonConTexto empezar;
    BotonConTexto encargar;
    BotonConTexto despachar;
    BotonConTexto reiniciar;
    BotonConTexto salir;
    std::vector<BotonConTexto *> todos;

    Botones(sf::Font &font, int pos_y_bajo_etiquetas);
};
