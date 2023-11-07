#include "paneles.h"
#include "../shared.h"
#include "basicos_vista.h"
#include "etiquetas/etiquetas.h"
#include <SFML/Graphics.hpp>
#include <cassert>
#include <iostream>

namespace medidas {
    constexpr int GROSOR_BORDE_PANEL = 3;
} // namespace medidas

const std::map<IndicePanel, std::string> titulos_paneles = {
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

Paneles::Paneles() {
    for (auto indice : paneles_posibles) {
        contenido.emplace(indice, crear_panel_estandar(indice));
    }
}

void Paneles::dibujar(sf::RenderWindow &ventana) {
    dibujar_elementos(ventana, contenido);
}

TitulosPaneles::TitulosPaneles(const sf::Font &font) : ObjetoConFont(font) {
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
    for (auto &[indice, texto_crudo] : titulos_paneles) {
        contenido.emplace(indice, crea_titulo(indice, texto_crudo));
    }
}

void TitulosPaneles::dibujar(sf::RenderWindow &ventana) {
    dibujar_elementos(ventana, contenido);
}

PanelesCompletos::PanelesCompletos(const sf::Font &font)
    : ObjetoConFont(font), titulos_paneles(font) {}

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
    barras_progreso_con_nombres = crear_barras_progreso( //
        preparacion, pos_panel, font
    );
    for (auto &bpn : barras_progreso_con_nombres) {
        bpn.dibujar(ventana);
    }
}
