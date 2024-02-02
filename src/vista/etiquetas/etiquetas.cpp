#include "etiquetas.h"
#include "../basicos_vista.h"
#include "../cadenas.h"
#include "../componentes/crear_etiqueta.h"
#include "../componentes/etiqueta.h"
#include "../presentacion_vista.h"
#include "etiquetas_barra_estado.h"
#include "etiquetas_info.h"
#include <SFML/Graphics/RenderTarget.hpp>

namespace medidas {
    constexpr int TAMANO_FUENTE_TITULO_PANELES = 36;
} // namespace medidas

namespace estilos {
    const EstiloTexto TITULO_PANEL = {
        medidas::TAMANO_FUENTE_TITULO_PANELES, sf::Color::Green
    };
}

///////////////////////////////////////////
// EtiquetasGenerales
//////////////////////////////////////////

EtiquetasGenerales::EtiquetasGenerales() {
    info = std::make_shared<EtiquetasInfo>();
    barra_estado = std::make_shared<EtiquetasBarraEstado>();
    add_child(info);
    add_child(barra_estado);
}

EtiquetasGenerales::~EtiquetasGenerales() = default;

void EtiquetasGenerales::setup(
    const std::string &instr,         //
    const NumNivelOpcional &num_nivel //
) {
    info->setup(instr, num_nivel);
}

void EtiquetasGenerales::set_presentacion_vista(
    std::shared_ptr<PresentacionVista> presentacion_vista
) {
    info->set_presentacion_vista(presentacion_vista);
}

void EtiquetasGenerales::actualizar_barra_estado(
    const sf::Time &tiempo_real_actual, const sf::Time &tiempo_juego_actual
) {
    barra_estado->actualizar(tiempo_real_actual, tiempo_juego_actual);
}

void EtiquetasGenerales::dibujar_barra_estado(sf::RenderTarget &target) {
    target.draw(*barra_estado);
}

void EtiquetasGenerales::dibujar_info(sf::RenderTarget &target) const {
    target.draw(*info);
}

void EtiquetasGenerales::draw(
    sf::RenderTarget &, //
    sf::RenderStates    //
) const {
    // No implementado
}

///////////////////////////////////////////
// FabricaEtiquetasTituloPanel
//////////////////////////////////////////

sf::Vector2f FabricaEtiquetasTituloPanel::get_posicion_etiqueta_titulo_panel(
    const sf::Vector2f &posicion_panel
) {
    auto pos_x =
        (posicion_panel.x) + static_cast<float>(medidas::MARGEN_IZQ_ETIQUETAS);
    auto pos_y =
        posicion_panel.y + static_cast<float>(medidas::FILA_TITULOS_PANELES);
    return sf::Vector2f(pos_x, pos_y);
}

/* Usando posicion_panel */
std::shared_ptr<Etiqueta> FabricaEtiquetasTituloPanel::crearEtiquetaTituloPanel(
    const sf::Vector2f &posicion_panel, const std::string &texto_crudo
) const {
    const auto posicion = get_posicion_etiqueta_titulo_panel(posicion_panel);
    const auto texto = interpolar_unicode(texto_crudo);
    return crear_etiqueta(
        texto, estilos::TITULO_PANEL, posicion,
        "etiqueta titulo panel " + texto_crudo
    );
}
