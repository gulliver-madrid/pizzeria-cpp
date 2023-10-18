#pragma once

#include "../../general.h"
#include "../../shared.h"
#include <SFML/Graphics.hpp>
#include <memory>

struct Globales;

struct EtiquetasContadores;
struct EtiquetasInfo;

///////////////////////////////////////////
// EtiquetasGenerales
//////////////////////////////////////////

/* Agrupa las etiquetas principales para un nivel determinado */
struct EtiquetasGenerales {
  private:
    const sf::Font &font;
    std::unique_ptr<EtiquetasContadores> contadores;
    std::unique_ptr<EtiquetasInfo> info;

  public:
    EtiquetasGenerales(
        const EsSistemaEstatico &es_estatico, const sf::Font &font
    );
    EtiquetasGenerales(const EtiquetasGenerales &) = delete;
    EtiquetasGenerales &operator=(const EtiquetasGenerales &) = delete;
    ~EtiquetasGenerales();

    void setup(
        const std::string &instr,                   //
        const NumNivel &,                           //
        const modelo::TiposDePizza &tp_disponibles, //
        std::optional<int> objetivo                 //
    );

    void actualizar_y_dibujar_contadores(
        const modelo::PizzasAContadores &pizzas_a_contadores, //
        const modelo::Pedidos &pedidos,                       //
        sf::RenderWindow &ventana                             //
    );

    void dibujar_instrucciones(sf::RenderWindow &ventana);
    void dibujar_resultado(sf::RenderWindow &ventana);
};

///////////////////////////////////////////
// FabricaEtiquetasTituloPanel
//////////////////////////////////////////

struct FabricaEtiquetasTituloPanel {
  private:
    const sf::Font &font;
    static sf::Vector2f get_posicion_etiqueta_titulo_panel( //
        const sf::Vector2f &posicion_panel
    );

  public:
    FabricaEtiquetasTituloPanel(const sf::Font &font) : font(font) {}
    sf::Text crearEtiquetaTituloPanel(
        const sf::Vector2f &posicion_panel, const std::string &texto_crudo
    ) const;
};
