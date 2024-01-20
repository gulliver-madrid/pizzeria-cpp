#pragma once

#include "../../modelo/control_pizzas.h"
#include "../../modelo/modelo.h"
#include "../../shared/num_nivel.h"
#include "../componente.h"
#include "../presentacion_vista.h"
#include "../vista_shared.h"
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <optional>

namespace sf {
    class Text;
    class RenderTarget;
    class RenderTarget;
    class Time;
} // namespace sf

class Etiqueta;
class EtiquetasBarraEstado;
class EtiquetasPreparadas;
class EtiquetasPedidos;
struct EtiquetasInfo;
struct Globales;

///////////////////////////////////////////
// EtiquetasGenerales
//////////////////////////////////////////

/* Agrupa las etiquetas principales para un nivel determinado */
struct EtiquetasGenerales : public ComponenteConFont {
  private:
    // std::shared_ptr<EtiquetasPreparadas> etiquetas_preparadas;
    std::shared_ptr<EtiquetasPedidos> etiquetas_pedidos;
    std::unique_ptr<EtiquetasInfo> info;
    std::unique_ptr<EtiquetasBarraEstado> barra_estado;

  public:
    EtiquetasGenerales(const OptionalFont &);
    EtiquetasGenerales(const EtiquetasGenerales &) = delete;
    EtiquetasGenerales &operator=(const EtiquetasGenerales &) = delete;
    ~EtiquetasGenerales();

    void setup(
        const std::string &instr,                   //
        const NumNivelOpcional &,                   //
        const dominio::TiposDePizza &tp_disponibles //
    );

    void set_presentacion_vista(
        std::shared_ptr<PresentacionVista> presentacion_vista //
    );

    void actualizar_pedidos(const modelo::Pedidos &pedidos //
    );

    void actualizar_barra_estado(
        const sf::Time &tiempo_real_actual, const sf::Time &tiempo_juego_actual
    );

    void dibujar_pedidos(sf::RenderTarget &target) const;
    void dibujar_barra_estado(sf::RenderTarget &target);
    void dibujar_info(sf::RenderTarget &target) const;
    virtual void draw(
        sf::RenderTarget &target, //
        sf::RenderStates states   //
    ) const override;
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
    FabricaEtiquetasTituloPanel(const OptionalFont &font)
        : ObjetoConFont(font) {}
    std::shared_ptr<Etiqueta> crearEtiquetaTituloPanel(
        const sf::Vector2f &posicion_panel, const std::string &texto_crudo
    ) const;
};
