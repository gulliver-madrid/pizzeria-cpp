#include "etiquetas.h"
#include "../basicos_vista.h"
#include "../cadenas.h"
#include "../componentes/varios.h"
#include "etiquetas_barra_estado.h"
#include "etiquetas_contadores.h"
#include "etiquetas_info.h"

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

EtiquetasGenerales::EtiquetasGenerales(
    const EsSistemaEstatico &es_estatico, const sf::Font &font
)
    : font(font) {
    contadores = std::make_unique<EtiquetasContadores>(es_estatico, font);
    info = std::make_unique<EtiquetasInfo>(font);
    barra_estado = std::make_unique<EtiquetasBarraEstado>(font);
}

EtiquetasGenerales::~EtiquetasGenerales() = default;

void EtiquetasGenerales::setup(
    const std::string &instr,                   //
    const NumNivel &num_nivel,                  //
    const modelo::TiposDePizza &tp_disponibles, //
    const std::optional<int> objetivo_estatico  //
) {
    info->setup(instr, num_nivel, objetivo_estatico);
    contadores->setup(tp_disponibles);
}

void EtiquetasGenerales::actualizar_y_dibujar_contadores(
    const modelo::PizzasAContadores &pizzas_a_contadores, //
    const modelo::Pedidos &pedidos,                       //
    sf::RenderWindow &ventana                             //
) {
    contadores->actualizar(pizzas_a_contadores, pedidos);
    contadores->dibujar(ventana);
}

void EtiquetasGenerales::dibujar_instrucciones(sf::RenderWindow &ventana) {
    ventana.draw(info->instrucciones);
}
void EtiquetasGenerales::dibujar_resultado(sf::RenderWindow &ventana) {
    ventana.draw(info->resultado);
}

void EtiquetasGenerales::dibujar_barra_estado(sf::RenderWindow &ventana) {
    barra_estado->dibujar(ventana);
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
