#pragma once

#include "../../general.h"
#include "../../shared.h"
#include "etiquetas_info.h"
#include <SFML/Graphics.hpp>
#include <memory>

struct Globales;

struct EtiquetasContadores;

/* Agrupa las etiquetas principales para un nivel determinado */
struct EtiquetasGenerales {
  private:
    const sf::Font &font;
    std::unique_ptr<EtiquetasContadores> contadores;

  public:
    EtiquetasInfo info;
    EtiquetasGenerales(bool es_estatico, const sf::Font &font);
    EtiquetasGenerales(const EtiquetasGenerales &) = delete;
    EtiquetasGenerales &operator=(const EtiquetasGenerales &) = delete;
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

struct FabricaEtiquetasTituloPanel {
  private:
    const sf::Font &font;

  public:
    FabricaEtiquetasTituloPanel(const sf::Font &font) : font(font) {}
    sf::Text crearEtiquetaTituloPanel(
        const sf::Vector2f &posicion_panel, const std::string &texto
    );
};
