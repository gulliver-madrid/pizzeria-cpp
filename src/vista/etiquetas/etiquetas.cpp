#include "etiquetas.h"
#include "../basicos_vista.h"
#include "../cadenas.h"
#include "../componentes/varios.h"
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

EtiquetasGenerales::EtiquetasGenerales(const sf::Font &font)
    : ObjetoConFont(font) {
    contadores = std::make_unique<EtiquetasContadores>(font);
    info = std::make_unique<EtiquetasInfo>(font);
    barra_estado = std::make_unique<EtiquetasBarraEstado>(font);
}

EtiquetasGenerales::~EtiquetasGenerales() = default;

void EtiquetasGenerales::setup(
    const std::string &instr,                   //
    const NumNivel &num_nivel,                  //
    const dominio::TiposDePizza &tp_disponibles //
) {
    info->setup(instr, num_nivel);
    contadores->setup(tp_disponibles);
}

void EtiquetasGenerales::actualizar_contadores(
    const VistaPizzasToStrings &vista_preparadas, //
    const modelo::Pedidos &pedidos                //

) {
    contadores->actualizar(vista_preparadas, pedidos);
}

void EtiquetasGenerales::actualizar_barra_estado(
    const sf::Time &tiempo_real_actual, const sf::Time &tiempo_juego_actual
) {
    barra_estado->actualizar(tiempo_real_actual, tiempo_juego_actual);
}
void EtiquetasGenerales::cambiar_visibilidad_instrucciones(bool visibilidad) {
    info->mostrar_instrucciones = visibilidad;
}
void EtiquetasGenerales::cambiar_visibilidad_resultado(bool visibilidad) {
    info->mostrar_resultado = visibilidad;
}

void EtiquetasGenerales::dibujar_contadores(sf::RenderTarget &target) {
    target.draw(*contadores);
}

void EtiquetasGenerales::dibujar_barra_estado(sf::RenderTarget &target) {
    target.draw(*barra_estado);
}

void EtiquetasGenerales::dibujar_info(sf::RenderTarget &target) const {
    target.draw(*info);
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
