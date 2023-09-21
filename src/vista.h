#pragma once

#include "componentes.h"
#include "tiempo.h"
#include <vector>

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
    void dibujar(sf::RenderWindow &ventana);
};

struct PorcentajeVisual {
    sf::RectangleShape fondo;
    sf::RectangleShape relleno;
};
struct PorcentajeVisualConNombre {
    sf::Text etiqueta;
    PorcentajeVisual pv;
};

struct Paneles {
    sf::RectangleShape en_preparacion;
    sf::RectangleShape preparadas;
    sf::RectangleShape pedidos;
    Paneles();

    void dibujar(sf::RenderWindow &window);
};

std::vector<PorcentajeVisualConNombre> crear_visualizaciones_porcentajes(
    const std::vector<int> &porcentajes,
    const std::vector<std::string> &nombres, sf::Font &font
);

struct TitulosPaneles {
    sf::Text en_preparacion;
    sf::Text preparadas;
    sf::Text pedidos;

    void dibujar(sf::RenderWindow &window);
};

struct PanelesCompletos {
    Paneles paneles;
    TitulosPaneles titulos_paneles;
    std::vector<PorcentajeVisualConNombre> porcentajes_visuales_con_nombres;
    bool visible = false;

    PanelesCompletos(sf::Font &font);
    void dibujar(
        sf::RenderWindow &ventana, std::vector<int> &porcentajes,
        std::vector<std::string> &nombres, sf::Font &font
    );
};
