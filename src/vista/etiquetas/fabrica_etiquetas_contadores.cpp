#include "fabrica_etiquetas_contadores.h"
#include "../basicos_vista.h"
#include "../componentes/varios.h"

namespace medidas {
    constexpr int TAMANO_FUENTE_ETIQUETAS = 24;
    constexpr int DESPLAZAMIENTO_VERTICAL_ETIQUETAS_PIZZAS_PREPARADAS = 50;
    constexpr int DESPLAZAMIENTO_VERTICAL_ETIQUETAS_PIZZAS_SERVIDAS = 50;
} // namespace medidas

namespace estilos {
    const EstiloTexto CONTADORES = {
        medidas::TAMANO_FUENTE_ETIQUETAS, sf::Color::White
    };
}

using basicos_vista::obtener_posicion_panel;

///////////////////////////////////////////
// FabricaEtiquetasContadores (private)
//////////////////////////////////////////

/*
 * Obtiene la posicion de una etiqueta para un contador de pizzas
 */
sf::Vector2f FabricaEtiquetasContadores::_obtener_posicion_etiqueta(
    const sf::Vector2f pos_panel,     //
    const size_t indice_etiqueta,     //
    const int desplazamiento_vertical //
) const {
    const auto pos_x = pos_panel.x + medidas::MARGEN_IZQ_ETIQUETAS;
    const auto pos_y = pos_panel.y + medidas::FILA_CONTENIDO_PANEL +
                       desplazamiento_vertical * indice_etiqueta;
    return sf::Vector2f(pos_x, pos_y);
}

/*
 * Crea una etiqueta para un contador (dependiendo del panel tendra uno u
 * otro significado)
 */
sf::Text FabricaEtiquetasContadores::_crear_etiqueta( //
    sf::Vector2f posicion
) const {
    return crearEtiqueta("", estilos::CONTADORES, font, posicion);
}

///////////////////////////////////////////
// FabricaEtiquetasContadores (public)
//////////////////////////////////////////

FabricaEtiquetasContadores::FabricaEtiquetasContadores(const OptionalFont &font)
    : ObjetoConFont(font){};

/*
 * Crea una etiqueta de pizzas preparadas
 */
sf::Text
FabricaEtiquetasContadores::crearEtiquetaPizzasPreparadas(size_t indice_etiqueta
) const {
    const auto indice_panel = IndicePanel::PANEL_PREPARADAS;
    const auto posicion_panel = obtener_posicion_panel(indice_panel);
    const auto desplazamiento =
        medidas::DESPLAZAMIENTO_VERTICAL_ETIQUETAS_PIZZAS_PREPARADAS;
    const auto posicion = _obtener_posicion_etiqueta(
        posicion_panel, indice_etiqueta, desplazamiento
    );
    return _crear_etiqueta(posicion);
}
