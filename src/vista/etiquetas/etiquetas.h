#pragma once

#include "../../modelo/modelo_shared.h"
#include "../componentes/componente.h"
#include "../presentacion_vista.h"
#include "../presentaciones.h"
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
class EtiquetasInfo;
class NumNivelOpcional;
class Globales;

///////////////////////////////////////////
// EtiquetasGenerales
//////////////////////////////////////////

/* Agrupa las etiquetas principales para un nivel determinado */
struct EtiquetasGenerales : public ComponenteConFont {
  private:
    std::shared_ptr<EtiquetasInfo> info;
    std::shared_ptr<EtiquetasBarraEstado> barra_estado;

  public:
    EtiquetasGenerales();
    EtiquetasGenerales(const EtiquetasGenerales &) = delete;
    EtiquetasGenerales &operator=(const EtiquetasGenerales &) = delete;
    ~EtiquetasGenerales();

    void setup(
        const std::string &instr, //
        const NumNivelOpcional &  //
    );

    void set_presentacion_vista(std::shared_ptr<PresentacionVista>);

    void actualizar_barra_estado(const VistaBarraEstado &);

    void dibujar_barra_estado(sf::RenderTarget &);
    void dibujar_info(sf::RenderTarget &) const;
    virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
};

///////////////////////////////////////////
// FabricaEtiquetasTituloPanel
//////////////////////////////////////////

class FabricaEtiquetasTituloPanel {
  private:
    static sf::Vector2f get_posicion_etiqueta_titulo_panel( //
        const sf::Vector2f &posicion_panel
    );

  public:
    std::shared_ptr<Etiqueta> crearEtiquetaTituloPanel(
        const sf::Vector2f &posicion_panel, const std::string &texto_crudo
    ) const;
};
