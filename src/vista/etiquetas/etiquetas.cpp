#include "etiquetas.h"
#include "../cadenas.h"
#include "../componentes/varios.h"
#include "../vista_basics.h"
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
}

EtiquetasGenerales::~EtiquetasGenerales() = default;

void EtiquetasGenerales::setup(
    const std::string &instr,                             //
    const NumNivel &num_nivel,                            //
    const std::vector<modelo::TipoPizza> &tp_disponibles, //
    int total_objetivos                                   //
) {
    info->setup(instr, num_nivel, total_objetivos);
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
    const sf::Vector2f &posicion_panel, const std::string &texto
) {
    const auto posicion = get_posicion_etiqueta_titulo_panel(posicion_panel);
    auto etiqueta = crearEtiqueta(estilos::TITULO_PANEL, font, posicion);
    etiqueta.setString(interpolar_unicode(texto));
    return etiqueta;
}
