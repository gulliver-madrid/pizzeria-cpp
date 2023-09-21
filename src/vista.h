#pragma once

#include "componentes.h"
#include "dominio.h"
#include "tiempo.h"
#include "vista_basics.h"
#include <vector>

sf::Text
crearEtiquetaTituloPanel(const sf::Font &, IndicePanel, const std::string &);
sf::Text crearEtiquetaContador(const sf::Font &, int indice);
sf::Text crearEtiquetaPizzasPreparadas(const sf::Font &, int indice);

struct BarraProgreso {
    sf::RectangleShape fondo;
    sf::RectangleShape relleno;
};
struct BarraProgresoConNombre {
    sf::Text etiqueta;
    BarraProgreso bp;
};

struct Paneles {
    sf::RectangleShape encargar;
    sf::RectangleShape en_preparacion;
    sf::RectangleShape preparadas;
    sf::RectangleShape pedidos;

    Paneles();
    void dibujar(sf::RenderWindow &window);
};

std::vector<BarraProgresoConNombre> crear_visualizaciones_porcentajes(
    const std::vector<PorcentajeConTipoPizza> &porcentajes, sf::Font &font
);

struct TitulosPaneles {
    sf::Text encargar;
    sf::Text en_preparacion;
    sf::Text preparadas;
    sf::Text pedidos;

    void dibujar(sf::RenderWindow &window);
};

struct PanelesCompletos {
    Paneles paneles;
    TitulosPaneles titulos_paneles;
    std::vector<BarraProgresoConNombre> porcentajes_visuales_con_nombres;
    bool visible = false;

    PanelesCompletos(sf::Font &font);
    void dibujar(
        sf::RenderWindow &ventana,
        std::vector<PorcentajeConTipoPizza> &porcentajes, sf::Font &font
    );
};
