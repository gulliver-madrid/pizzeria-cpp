#pragma once

#include "../general.h"
#include "../shared.h"
#include <SFML/Graphics.hpp>
#include <memory>

struct Globales;

struct EtiquetasContadores;

struct EtiquetasInfo {
    sf::Text instrucciones;
    sf::Text resultado;
};

/* Agrupa las etiquetas principales para un nivel determinado */
struct EtiquetasGenerales {
  private:
    const sf::Font &font;
    std::unique_ptr<EtiquetasContadores> contadores;

  public:
    EtiquetasInfo info;
    EtiquetasGenerales(bool es_estatico, const sf::Font &font);
    ~EtiquetasGenerales();

    void setup(
        const std::string &instr,                     //
        NumNivel num_nivel,                           //
        const std::vector<TipoPizza> &tp_disponibles, //
        int total_objetivos
    );

    void actualizar_y_dibujar_contadores(
        const PizzasAContadores &pizzas_a_contadores, //
        const Pedidos &pedidos,                       //
        sf::RenderWindow &ventana                     //
    );
};

sf::Text crearEtiquetaTituloPanel(
    const sf::Font &font, const sf::Vector2f &posicion_panel,
    const std::string &texto
);
