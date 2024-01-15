#include "paneles.h"
#include "../templates/dibujar_elementos.h"
#include "basicos_vista.h"
#include "etiquetas/etiquetas.h"
#include <cassert>
#include <iostream>

namespace medidas {
    constexpr int GROSOR_BORDE_PANEL = 3;
} // namespace medidas

const std::map<IndicePanel, std::string> texto_titulos_paneles = {
    {IndicePanel::PANEL_ENCARGAR, "Encargar"},
    {IndicePanel::PANEL_EN_PREPARACION, "En preparaci%on"},
    {IndicePanel::PANEL_PREPARADAS, "Preparadas"},
    {IndicePanel::PANEL_PEDIDOS, "Pedidos"}
};

namespace {
    sf::RectangleShape _crearPanelVertical(float x, float y) {
        auto rect = sf::RectangleShape(
            sf::Vector2f(medidas::ANCHO_PANEL, medidas::ALTO_PANEL)
        );
        rect.setPosition(sf::Vector2f(x, y));
        rect.setFillColor(sf::Color(40, 40, 40, 200));
        rect.setOutlineColor(sf::Color::Green);
        rect.setOutlineThickness(medidas::GROSOR_BORDE_PANEL);
        return rect;
    }

    sf::RectangleShape crear_panel_estandar(IndicePanel indice) {
        auto pos_panel = basicos_vista::obtener_posicion_panel(indice);
        return _crearPanelVertical(pos_panel.x, pos_panel.y);
    }
} // namespace

Panel::Panel(IndicePanel indice, sf::Text etiqueta)
    : indice(indice), forma(crear_panel_estandar(indice)),
      etiqueta_titulo(etiqueta) {}

void Panel::draw(
    sf::RenderTarget &target, //
    sf::RenderStates states   //
) const {
    target.draw(forma);
    target.draw(etiqueta_titulo);
}

Paneles::Paneles(const sf::Font &font) : ObjetoConFont(font) {
    const FabricaEtiquetasTituloPanel fabrica(font);
    const auto crea_titulo = [&fabrica](
                                 const IndicePanel indice,      //
                                 const std::string &texto_crudo //
                             ) {
        return fabrica.crearEtiquetaTituloPanel(
            basicos_vista::obtener_posicion_panel(indice), //
            texto_crudo
        );
    };

    for (auto indice : paneles_posibles) {
        contenido.emplace(
            indice,
            Panel(indice, crea_titulo(indice, texto_titulos_paneles.at(indice)))
        );
    }
}

void Paneles::actualizar(const VistaPreparacionPizzas &vista_preparacion //
) {
    if (!visible)
        return;
    auto pos_panel = basicos_vista::obtener_posicion_panel( //
        IndicePanel::PANEL_EN_PREPARACION
    );
    barras_progreso_con_nombres = crear_barras_progreso( //
        vista_preparacion, pos_panel, font
    );
}

void Paneles::draw(
    sf::RenderTarget &target, //
    sf::RenderStates states   //
) const {
    if (!visible)
        return;
    dibujar_elementos(target, contenido);
    for (auto &bpn : barras_progreso_con_nombres) {
        target.draw(bpn);
    }
}
