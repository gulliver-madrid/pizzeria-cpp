#include "paneles.h"
#include "basicos_vista.h"
#include "etiquetas/etiquetas.h"
#include <SFML/Graphics.hpp>
#include <cassert>
#include <iostream>

namespace medidas {
    constexpr int GROSOR_BORDE_PANEL = 3;
} // namespace medidas

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

Paneles::Paneles() {
    encargar = crear_panel_estandar(IndicePanel::PANEL_ENCARGAR);
    en_preparacion = crear_panel_estandar(IndicePanel::PANEL_EN_PREPARACION);
    preparadas = crear_panel_estandar(IndicePanel::PANEL_PREPARADAS);
    pedidos = crear_panel_estandar(IndicePanel::PANEL_PEDIDOS);
}

void Paneles::dibujar(sf::RenderWindow &window) {
    window.draw(encargar);
    window.draw(en_preparacion);
    window.draw(preparadas);
    window.draw(pedidos);
}

void TitulosPaneles::dibujar(sf::RenderWindow &ventana) {
    ventana.draw(encargar);
    ventana.draw(en_preparacion);
    ventana.draw(preparadas);
    ventana.draw(pedidos);
}

PanelesCompletos::PanelesCompletos(const sf::Font &font) : font(font) {
    const FabricaEtiquetasTituloPanel fabrica(font);
    const auto crea_titulo = [&fabrica](
                                 const IndicePanel indice_panel,
                                 const std::string texto_crudo
                             ) {
        return fabrica.crearEtiquetaTituloPanel(
            basicos_vista::obtener_posicion_panel(indice_panel), //
            texto_crudo
        );
    };
    titulos_paneles = {
        crea_titulo(IndicePanel::PANEL_ENCARGAR, "Encargar"),
        crea_titulo(IndicePanel::PANEL_EN_PREPARACION, "En preparaci%on"),
        crea_titulo(IndicePanel::PANEL_PREPARADAS, "Preparadas"),
        crea_titulo(IndicePanel::PANEL_PEDIDOS, "Pedidos")
    };
}

void PanelesCompletos::dibujar(
    sf::RenderWindow &ventana,                 //
    const EstadoPreparacionPizzas &preparacion //

) {
    if (!visible)
        return;
    paneles.dibujar(ventana);
    titulos_paneles.dibujar(ventana);
    auto pos_panel = basicos_vista::obtener_posicion_panel( //
        IndicePanel::PANEL_EN_PREPARACION
    );
    barras_progreso_con_nombres =
        crear_barras_progreso(preparacion, pos_panel, font);
    for (auto &bpn : barras_progreso_con_nombres) {
        bpn.dibujar(ventana);
    }
}
