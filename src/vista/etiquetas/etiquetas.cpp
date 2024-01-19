#include "etiquetas.h"
#include "../basicos_vista.h"
#include "../cadenas.h"
#include "../componentes/varios.h"
#include "../presentacion_vista.h"
#include "etiquetas_barra_estado.h"
#include "etiquetas_contadores.h"
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

EtiquetasGenerales::EtiquetasGenerales(const OptionalFont &font) {
    set_font(font);
    etiquetas_pedidos = std::make_shared<EtiquetasPedidos>();
    info = std::make_unique<EtiquetasInfo>(font);
    barra_estado = std::make_unique<EtiquetasBarraEstado>(font);
    add_child(etiquetas_pedidos);
}

EtiquetasGenerales::~EtiquetasGenerales() = default;

void EtiquetasGenerales::setup(
    const std::string &instr,                   //
    const NumNivelOpcional &num_nivel,          //
    const dominio::TiposDePizza &tp_disponibles //
) {
    info->setup(instr, num_nivel);
}

void EtiquetasGenerales::set_presentacion_vista(
    std::shared_ptr<PresentacionVista> presentacion_vista
) {
    info->set_presentacion_vista(presentacion_vista);
}

void EtiquetasGenerales::actualizar_contadores(
    const PizzasToStrings &vista_preparadas, //
    const modelo::Pedidos &pedidos           //
) {
    etiquetas_pedidos->actualizar(pedidos);
}

void EtiquetasGenerales::actualizar_barra_estado(
    const sf::Time &tiempo_real_actual, const sf::Time &tiempo_juego_actual
) {
    barra_estado->actualizar(tiempo_real_actual, tiempo_juego_actual);
}

void EtiquetasGenerales::dibujar_pedidos(sf::RenderTarget &target) const {
    target.draw(*etiquetas_pedidos);
}

void EtiquetasGenerales::dibujar_barra_estado(sf::RenderTarget &target) {
    target.draw(*barra_estado);
}

void EtiquetasGenerales::dibujar_info(sf::RenderTarget &target) const {
    target.draw(*info);
}

void EtiquetasGenerales::draw(
    sf::RenderTarget &target, //
    sf::RenderStates states   //
) const {
    // No implementado
}

///////////////////////////////////////////
// FabricaEtiquetasTituloPanel
//////////////////////////////////////////

sf::Vector2f FabricaEtiquetasTituloPanel::get_posicion_etiqueta_titulo_panel(
    const sf::Vector2f &posicion_panel
) {
    int pos_x = posicion_panel.x + medidas::MARGEN_IZQ_ETIQUETAS;
    int pos_y = posicion_panel.y + medidas::FILA_TITULOS_PANELES;
    return sf::Vector2f(pos_x, pos_y);
}

/* Usando posicion_panel */
sf::Text FabricaEtiquetasTituloPanel::crearEtiquetaTituloPanel(
    const sf::Vector2f &posicion_panel, const std::string &texto_crudo
) const {
    const auto posicion = get_posicion_etiqueta_titulo_panel(posicion_panel);
    const auto texto = interpolar_unicode(texto_crudo);
    return crearEtiqueta(texto, estilos::TITULO_PANEL, font, posicion);
}
