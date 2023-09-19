#pragma once

#include "componentes.h"

sf::Text
crearEtiqueta(int tamano, sf::Font &font, sf::Color color = sf::Color::White);
BotonConTexto crearBotonConTexto(
    std::string texto, sf::Color color_fondo, sf::Vector2i posicion,
    sf::Font &font, sf::Color color_texto = sf::Color::White
);
sf::Text crearEtiquetaContador(sf::Font &font);
sf::Text crearEtiquetaPizzasPreparadas(sf::Font &font);

struct Botones {

    BotonConTexto empezar;
    BotonConTexto encargar;
    BotonConTexto despachar;
    BotonConTexto reiniciar;
    BotonConTexto salir;
    std::vector<BotonConTexto *> todos;

    Botones(sf::Font &);
};

sf::RectangleShape
crearPanelVertical(float x, float y, float ancho, float alto);

const auto margen_izq_paneles = 50;
const auto desplazamiento_lateral = 520;
const auto margen_top_paneles = 50;
const auto ancho_panel = 480;
const auto alto_panel = 700;

struct Paneles {
    sf::RectangleShape en_preparacion = crearPanelVertical(
        margen_izq_paneles, margen_top_paneles, ancho_panel, alto_panel
    );
    sf::RectangleShape preparadas = crearPanelVertical(
        margen_izq_paneles + desplazamiento_lateral, margen_top_paneles,
        ancho_panel, alto_panel
    );
    sf::RectangleShape pedidos = crearPanelVertical(
        margen_izq_paneles + desplazamiento_lateral * 2, margen_top_paneles,
        ancho_panel, alto_panel
    );
    bool visible = false;

    void dibujar(sf::RenderWindow &window);
};
