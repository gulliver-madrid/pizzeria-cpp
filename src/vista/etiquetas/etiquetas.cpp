#include "etiquetas.h"
#include "../../templates.h"
#include "../cadenas.h"
#include "../componentes/varios.h"
#include "../vista_basics.h"
#include "etiquetas_contadores.h"
#include "fabrica_etiquetas.h"

namespace medidas {
    constexpr int TAMANO_FUENTE_TITULO_PANELES = 36;
} // namespace medidas
namespace estilos {
    const EstiloTexto TITULO_PANEL = {
        medidas::TAMANO_FUENTE_TITULO_PANELES, sf::Color::Green
    };
}

sf::Vector2f
get_posicion_etiqueta_titulo_panel(const sf::Vector2f &posicion_panel) {
    int pos_x = posicion_panel.x + medidas::MARGEN_IZQ_ETIQUETAS;
    int pos_y = posicion_panel.y + medidas::FILA_TITULOS_PANELES;
    return sf::Vector2f(pos_x, pos_y);
}

/* Usando posicion_panel */
sf::Text FabricaEtiquetasTituloPanel::crearEtiquetaTituloPanel(
    const sf::Vector2f &posicion_panel, const std::string &texto
) {
    const auto posicion = get_posicion_etiqueta_titulo_panel(posicion_panel);
    const EstiloTextoConFuente estilo = {estilos::TITULO_PANEL, font};
    auto etiqueta = crearEtiqueta(estilo, posicion);
    etiqueta.setString(interpolar_unicode(texto));
    return etiqueta;
}

EtiquetasGenerales::EtiquetasGenerales(bool es_estatico, const sf::Font &font)
    : font(font) {
    contadores = std::make_unique<EtiquetasContadores>(es_estatico, font);
}

EtiquetasGenerales::~EtiquetasGenerales() = default;

void EtiquetasGenerales::setup(
    const std::string &instr,                     //
    NumNivel num_nivel,                           //
    const std::vector<TipoPizza> &tp_disponibles, //
    int total_objetivos                           //
) {
    const auto instrucciones =
        FabricaEtiquetasInfo::generar_etiqueta_instrucciones(
            font, instr, num_nivel, total_objetivos
        );
    const auto resultado =
        FabricaEtiquetasInfo::generar_etiqueta_resultado(font);
    info = {instrucciones, resultado};
    contadores->setup(tp_disponibles);
}

void EtiquetasGenerales::actualizar_y_dibujar_contadores(
    const PizzasAContadores &pizzas_a_contadores, //
    const Pedidos &pedidos,                       //
    sf::RenderWindow &ventana                     //
) {
    contadores->actualizar(pizzas_a_contadores, pedidos);
    contadores->dibujar(ventana);
}
