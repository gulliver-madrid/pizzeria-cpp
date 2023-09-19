#pragma once

#include "componentes.h"

enum IndicePanel {
    PANEL_EN_PREPARACION,
    PANEL_PREPARADAS,
    PANEL_PEDIDOS,
};

sf::Text crearEtiqueta(int, const sf::Font &, const sf::Color &);
BotonConTexto crearBotonConTexto(
    const std::string &, const sf::Color &color_fondo, const sf::Vector2i &,
    const sf::Font &, const sf::Color &color_texto = sf::Color::White
);
sf::Text
crearEtiquetaTituloPanel(const sf::Font &, IndicePanel, const std::string &);
sf::Text crearEtiquetaContador(const sf::Font &);
sf::Text crearEtiquetaPizzasPreparadas(const sf::Font &);

struct Botones {
    BotonConTexto empezar;
    BotonConTexto encargar;
    BotonConTexto despachar;
    BotonConTexto reiniciar;
    BotonConTexto salir;
    std::vector<BotonConTexto *> todos;

    Botones(sf::Font &);
};

struct Paneles {
    sf::RectangleShape en_preparacion;
    sf::RectangleShape preparadas;
    sf::RectangleShape pedidos;
    bool visible = false;
    Paneles();

    void dibujar(sf::RenderWindow &window);
};
