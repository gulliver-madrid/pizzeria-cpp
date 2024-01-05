#pragma once

#include "../../modelo/control_pizzas.h"
#include "../../modelo/modelo.h"
#include "../../shared.h"
#include "../vista_shared.h"
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <optional>

namespace sf {
    class Text;
    class RenderTarget;
    class RenderTarget;
} // namespace sf

struct EtiquetasBarraEstado;
struct EtiquetasContadores;
struct EtiquetasInfo;
struct Globales;

///////////////////////////////////////////
// EtiquetasGenerales
//////////////////////////////////////////

/* Agrupa las etiquetas principales para un nivel determinado */
struct EtiquetasGenerales : public ObjetoConFont {
  private:
    std::unique_ptr<EtiquetasContadores> contadores;
    std::unique_ptr<EtiquetasInfo> info;
    std::unique_ptr<EtiquetasBarraEstado> barra_estado;

  public:
    EtiquetasGenerales(const sf::Font &font);
    EtiquetasGenerales(const EtiquetasGenerales &) = delete;
    EtiquetasGenerales &operator=(const EtiquetasGenerales &) = delete;
    ~EtiquetasGenerales();

    void setup(
        const std::string &instr,                   //
        const NumNivel &,                           //
        const dominio::TiposDePizza &tp_disponibles //
    );

    void actualizar_contadores(
        const VistaPizzasToStrings &vista_preparadas, //
        const modelo::Pedidos &pedidos                //

    );
    void dibujar_contadores(sf::RenderTarget &target);

    void actualizar_barra_estado(
        const sf::Time &tiempo_real_actual, const sf::Time &tiempo_juego_actual
    );

    void dibujar_instrucciones(sf::RenderTarget &target);
    void dibujar_resultado(sf::RenderTarget &target);
    void dibujar_barra_estado(sf::RenderTarget &target);
};

///////////////////////////////////////////
// FabricaEtiquetasTituloPanel
//////////////////////////////////////////

struct FabricaEtiquetasTituloPanel : public ObjetoConFont {
  private:
    static sf::Vector2f get_posicion_etiqueta_titulo_panel( //
        const sf::Vector2f &posicion_panel
    );

  public:
    FabricaEtiquetasTituloPanel(const sf::Font &font) : ObjetoConFont(font) {}
    sf::Text crearEtiquetaTituloPanel(
        const sf::Vector2f &posicion_panel, const std::string &texto_crudo
    ) const;
};
