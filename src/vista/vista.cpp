#include "vista.h"
#include "../cadenas.h"
#include "vista_basics.h"
#include <SFML/Graphics.hpp>
#include <cassert>
#include <iostream>

#define COLOR_BARRA_PROGRESO_FONDO 230, 230, 230
#define COLOR_BARRA_PROGRESO_RELLENO 255, 140, 0 // 30, 144, 255
#define COLOR_BARRA_PROGRESO_TEXTO 0, 0, 0

sf::RectangleShape crearPanelVertical(float x, float y) {
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
    auto pos_panel = obtener_posicion_panel(indice);
    return crearPanelVertical(pos_panel.x, pos_panel.y);
}

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

std::vector<BarraProgresoConNombre> crear_barras_progreso(
    const EstadoPreparacionPizzas &preparacion, sf::Font &font
) {
    std::vector<BarraProgresoConNombre> vect{};
    auto pos_panel = obtener_posicion_panel(IndicePanel::PANEL_EN_PREPARACION);
    int pos_x = pos_panel.x + medidas::MARGEN_IZQ_ETIQUETAS;
    int pos_y_inicial = pos_panel.y + medidas::FILA_CONTENIDO_PANEL;
    int ancho = 300;
    int largo = 40;
    int i = 0;
    for (auto &porcentaje : preparacion.datos) {
        BarraProgresoConNombre bpn;
        BarraProgreso &bp = bpn.bp;
        bp.fondo = sf::RectangleShape(sf::Vector2f(ancho, largo));
        bp.relleno = sf::RectangleShape(
            sf::Vector2f(ancho * porcentaje.porcentaje / 100, largo)
        );
        bp.fondo.setFillColor(sf::Color(COLOR_BARRA_PROGRESO_FONDO));
        bp.relleno.setFillColor(sf::Color(COLOR_BARRA_PROGRESO_RELLENO));
        int offset_y = i * medidas::DIFERENCIA_VERTICAL_ENTRE_BARRAS_PROGRESO;
        int pos_y = pos_y_inicial + offset_y;
        bp.fondo.setPosition(pos_x, pos_y);
        bp.relleno.setPosition(pos_x, pos_y);
        bpn.etiqueta =
            sf::Text(tipo_pizza_to_string[porcentaje.tipo], font, 24);
        bpn.etiqueta.setFillColor(sf::Color(COLOR_BARRA_PROGRESO_TEXTO));
        bpn.etiqueta.setPosition(pos_x + 20, pos_y + 5);
        vect.push_back(bpn);
        i++;
    }
    return vect;
}

void TitulosPaneles::dibujar(sf::RenderWindow &ventana) {
    ventana.draw(encargar);
    ventana.draw(en_preparacion);
    ventana.draw(preparadas);
    ventana.draw(pedidos);
}

PanelesCompletos::PanelesCompletos(sf::Font &font) {
    titulos_paneles = {
        crearEtiquetaTituloPanel(
            font, obtener_posicion_panel(IndicePanel::PANEL_ENCARGAR),
            "Encargar"
        ),
        crearEtiquetaTituloPanel(
            font, obtener_posicion_panel(IndicePanel::PANEL_EN_PREPARACION),
            "En preparaci%on"
        ),
        crearEtiquetaTituloPanel(
            font, obtener_posicion_panel(IndicePanel::PANEL_PREPARADAS),
            "Preparadas"
        ),
        crearEtiquetaTituloPanel(
            font, obtener_posicion_panel(IndicePanel::PANEL_PEDIDOS), "Pedidos"
        )};
}

void PanelesCompletos::dibujar(
    sf::RenderWindow &ventana, const EstadoPreparacionPizzas &preparacion,
    sf::Font &font
) {
    if (!visible)
        return;
    paneles.dibujar(ventana);
    titulos_paneles.dibujar(ventana);
    barras_progreso_con_nombres = crear_barras_progreso(preparacion, font);
    for (auto &bpn : barras_progreso_con_nombres) {
        ventana.draw(bpn.bp.fondo);
        ventana.draw(bpn.bp.relleno);
        ventana.draw(bpn.etiqueta);
    }
}
