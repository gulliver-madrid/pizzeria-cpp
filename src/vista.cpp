#include "vista.h"
#include "cadenas.h"
#include <SFML/Graphics.hpp>
#include <cassert>
#include <iostream>

#define COLOR_BARRA_PROGRESO_FONDO 230, 230, 230
#define COLOR_BARRA_PROGRESO_RELLENO 30, 144, 255
#define COLOR_BARRA_PROGRESO_TEXTO 0, 0, 0

namespace medidas {
    constexpr int TAMANO_FUENTE_ETIQUETAS = 36;
    constexpr int MARGEN_IZQ_ETIQUETAS = 50;
    constexpr int TAMANO_TEXTO_BOTONES = 24;
    constexpr int MARGEN_LATERAL_BOTON = 25;
    constexpr int ANCHO_PANEL = 480;
    constexpr int ALTO_PANEL = 700;
    constexpr int GROSOR_BORDE_PANEL = 5;
    constexpr int POSICION_Y_ETIQUETAS = 200;
    constexpr int FILA_BOTONES_EJECUTIVOS = 600;
    constexpr int FILA_BOTONES_GENERALES = 800;
    constexpr int MARGEN_IZQ_PANELES = 50;
    constexpr int DESPLAZAMIENTO_LATERAL = 560;
    constexpr int MARGEN_TOP_PANELES = 50;
    constexpr int DIFERENCIA_VERTICAL_ENTRE_PORCENTAJES_VISUALES = 60;
} // namespace medidas

int obtener_posicion_x_panel(IndicePanel indice_panel) {
    return medidas::MARGEN_IZQ_PANELES +
           (medidas::DESPLAZAMIENTO_LATERAL * indice_panel);
}

sf::Text
crearEtiqueta(int tamano, const sf::Font &font, const sf::Color &color) {
    // Usamos un placeholder para poder obtener la altura
    sf::Text etiqueta("<Placeholder>", font, tamano);
    etiqueta.setFillColor(color);
    return etiqueta;
}

/* Crea un botón rectangular con texto */
BotonConTexto crearBotonConTexto(
    const std::string &texto, const sf::Color &color_fondo,
    const sf::Vector2i &posicion, const sf::Font &font,
    const sf::Color &color_texto
) {
    int x = posicion.x;
    int y = posicion.y;
    int margen = medidas::MARGEN_LATERAL_BOTON;
    // Primero creamos la etiqueta para usar sus límites en el Rect
    sf::Text etiqueta =
        crearEtiqueta(medidas::TAMANO_TEXTO_BOTONES, font, color_texto);
    etiqueta.setString(texto);
    etiqueta.setPosition(x + margen, y + margen);
    sf::FloatRect textRect = etiqueta.getGlobalBounds();

    // Rect
    sf::RectangleShape rect(
        sf::Vector2f(textRect.width + margen * 2, textRect.height + margen * 2)
    );
    rect.setFillColor(color_fondo);
    rect.setPosition(x, y);

    return BotonConTexto(rect, etiqueta);
};

Botones::Botones(sf::Font &font) {
    empezar = crearBotonConTexto(
        "Empezar", sf::Color::Green, sf::Vector2i(500, 450), font,
        sf::Color::Black
    );
    encargar = crearBotonConTexto(
        "Encargar pizza", sf::Color::Green,
        sf::Vector2i(
            obtener_posicion_x_panel(PANEL_EN_PREPARACION) +
                medidas::MARGEN_IZQ_ETIQUETAS,
            medidas::FILA_BOTONES_EJECUTIVOS
        ),
        font, sf::Color::Black
    );
    despachar = crearBotonConTexto(
        "Despachar pizza", sf::Color::Green,
        sf::Vector2i(
            obtener_posicion_x_panel(PANEL_PREPARADAS) +
                medidas::MARGEN_IZQ_ETIQUETAS,
            medidas::FILA_BOTONES_EJECUTIVOS
        ),
        font, sf::Color::Black
    );

    reiniciar = crearBotonConTexto(
        "Reiniciar", sf::Color::Blue,
        sf::Vector2i(1350, medidas::FILA_BOTONES_GENERALES), font
    );
    salir = crearBotonConTexto(
        "Salir", sf::Color::Red,
        sf::Vector2i(1600, medidas::FILA_BOTONES_GENERALES), font
    );

    todos = {&empezar, &encargar, &despachar, &reiniciar, &salir};
    assert(todos.size() == 5);
}

void Botones::dibujar(sf::RenderWindow &ventana) {
    for (auto boton_ptr : todos) {
        assert(boton_ptr != nullptr);
        boton_ptr->dibujar(ventana);
    }
}

sf::Text crearEtiquetaTituloPanel(
    const sf::Font &font, IndicePanel indice_panel, const std::string &texto
) {
    sf::Text etiqueta =
        crearEtiqueta(medidas::TAMANO_FUENTE_ETIQUETAS, font, sf::Color::White);
    etiqueta.setPosition(
        obtener_posicion_x_panel(indice_panel) + medidas::MARGEN_IZQ_ETIQUETAS,
        100
    );
    etiqueta.setString(interpolar_unicode(texto));
    etiqueta.setFillColor(sf::Color::Green);
    return etiqueta;
}

// Crea la etiqueta de texto que mostrará el contador
sf::Text crearEtiquetaContador(const sf::Font &font) {
    sf::Text etiqueta =
        crearEtiqueta(medidas::TAMANO_FUENTE_ETIQUETAS, font, sf::Color::White);
    etiqueta.setPosition(
        obtener_posicion_x_panel(PANEL_PEDIDOS) + medidas::MARGEN_IZQ_ETIQUETAS,
        medidas::POSICION_Y_ETIQUETAS
    );
    return etiqueta;
}
sf::Text crearEtiquetaPizzasPreparadas(const sf::Font &font) {
    sf::Text etiqueta =
        crearEtiqueta(medidas::TAMANO_FUENTE_ETIQUETAS, font, sf::Color::White);
    auto pos_x = obtener_posicion_x_panel(PANEL_PREPARADAS) +
                 medidas::MARGEN_IZQ_ETIQUETAS;
    etiqueta.setPosition(pos_x, medidas::POSICION_Y_ETIQUETAS);
    return etiqueta;
}

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
    return crearPanelVertical(
        obtener_posicion_x_panel(indice), medidas::MARGEN_TOP_PANELES
    );
}

Paneles::Paneles() {
    en_preparacion = crear_panel_estandar(PANEL_EN_PREPARACION);
    preparadas = crear_panel_estandar(PANEL_PREPARADAS);
    pedidos = crear_panel_estandar(PANEL_PEDIDOS);
}

void Paneles::dibujar(sf::RenderWindow &window) {
    window.draw(en_preparacion);
    window.draw(preparadas);
    window.draw(pedidos);
}

std::vector<PorcentajeVisualConNombre> crear_visualizaciones_porcentajes(
    const std::vector<int> &porcentajes,
    const std::vector<std::string> &nombres, sf::Font &font
) {
    assert(porcentajes.size() == nombres.size());
    std::vector<PorcentajeVisualConNombre> vect{};
    int i = 0;
    int pos_x = 100;
    int pos_y_inicial = 240;
    int ancho = 300;
    int largo = 40;
    for (auto porcentaje : porcentajes) {
        PorcentajeVisualConNombre pvn;
        PorcentajeVisual &pv = pvn.pv;
        pv.fondo = sf::RectangleShape(sf::Vector2f(ancho, largo));
        pv.relleno =
            sf::RectangleShape(sf::Vector2f(ancho * porcentaje / 100, largo));
        pv.fondo.setFillColor(sf::Color(COLOR_BARRA_PROGRESO_FONDO));
        pv.relleno.setFillColor(sf::Color(COLOR_BARRA_PROGRESO_RELLENO));
        int offset_y =
            i * medidas::DIFERENCIA_VERTICAL_ENTRE_PORCENTAJES_VISUALES;
        int pos_y = pos_y_inicial + offset_y;
        pv.fondo.setPosition(pos_x, pos_y);
        pv.relleno.setPosition(pos_x, pos_y);
        pvn.etiqueta = sf::Text(nombres[i], font, 24);
        pvn.etiqueta.setFillColor(sf::Color(COLOR_BARRA_PROGRESO_TEXTO));
        pvn.etiqueta.setPosition(pos_x + 20, pos_y + 5);
        vect.push_back(pvn);
        i++;
    }
    return vect;
}

void TitulosPaneles::dibujar(sf::RenderWindow &ventana) {
    ventana.draw(en_preparacion);
    ventana.draw(preparadas);
    ventana.draw(pedidos);
}

PanelesCompletos::PanelesCompletos(sf::Font &font) {
    sf::Text titulo_1 = crearEtiquetaTituloPanel(
        font, IndicePanel::PANEL_EN_PREPARACION, "En preparaci%on"
    );
    sf::Text titulo_2 = crearEtiquetaTituloPanel(
        font, IndicePanel::PANEL_PREPARADAS, "Preparadas"
    );
    sf::Text titulo_3 =
        crearEtiquetaTituloPanel(font, IndicePanel::PANEL_PEDIDOS, "Pedidos");
    titulos_paneles = {titulo_1, titulo_2, titulo_3};
}

void PanelesCompletos::dibujar(
    sf::RenderWindow &ventana, std::vector<int> &porcentajes,
    std::vector<std::string> &nombres, sf::Font &font
) {
    if (!visible)
        return;
    paneles.dibujar(ventana);
    titulos_paneles.dibujar(ventana);
    porcentajes_visuales_con_nombres =
        crear_visualizaciones_porcentajes(porcentajes, nombres, font);
    for (auto &tpv : porcentajes_visuales_con_nombres) {
        ventana.draw(tpv.pv.fondo);
        ventana.draw(tpv.pv.relleno);
        ventana.draw(tpv.etiqueta);
    }
}
