#include "vista.h"
#include "cadenas.h"
#include <SFML/Graphics.hpp>
#include <cassert>
#include <iostream>

#define COLOR_BARRA_PROGRESO_FONDO 230, 230, 230
#define COLOR_BARRA_PROGRESO_RELLENO 255, 140, 0 // 30, 144, 255
#define COLOR_BARRA_PROGRESO_TEXTO 0, 0, 0

namespace medidas {
    constexpr int TAMANO_FUENTE_ETIQUETAS = 36;
    constexpr int MARGEN_IZQ_ETIQUETAS = 30;
    constexpr int TAMANO_TEXTO_BOTONES = 32;
    constexpr int MARGEN_BOTON = 20;
    constexpr int ANCHO_PANEL = 390;
    constexpr int ALTO_PANEL = 700;
    constexpr int GROSOR_BORDE_PANEL = 3;
    constexpr int FILA_CONTENIDO_PANEL = 200;
    constexpr int MARGEN_TOP_PANELES = 50;
    constexpr int DIFERENCIA_VERTICAL_ENTRE_BARRAS_PROGRESO = 60;
    constexpr int FILA_TITULOS_PANELES = 100;
    constexpr int FILA_BOTONES_EJECUTIVOS = 600;
    constexpr int FILA_BOTONES_GENERALES = 800;
    constexpr int MARGEN_IZQ_PANELES = 50;
    constexpr int DESPLAZAMIENTO_LATERAL = ANCHO_PANEL + 42;
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
    const sf::Color &color_texto, float escala
) {
    int x = posicion.x;
    int y = posicion.y;
    // La escala del margen es proporcional al cuadrado de la escala del botón
    int margen = medidas::MARGEN_BOTON * (escala * escala);
    // Primero creamos la etiqueta para usar sus límites en el Rect
    sf::Text etiqueta = crearEtiqueta(
        medidas::TAMANO_TEXTO_BOTONES * escala, font, color_texto
    );
    etiqueta.setString(texto);
    // Ajustamos para evitar un margen excesivo arriba y a la izquierda
    etiqueta.setPosition(x + margen * 0.7, y + margen * 0.7);
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
    encargar_margarita = crearBotonConTexto(
        "Margarita", sf::Color::Green,
        sf::Vector2i(
            obtener_posicion_x_panel(PANEL_ENCARGAR) +
                medidas::MARGEN_IZQ_ETIQUETAS,
            medidas::FILA_CONTENIDO_PANEL
        ),
        font, sf::Color::Black
    );
    despachar = crearBotonConTexto(
        "Despachar", sf::Color::Green,
        sf::Vector2i(
            obtener_posicion_x_panel(PANEL_PREPARADAS) +
                medidas::MARGEN_IZQ_ETIQUETAS + (medidas::ANCHO_PANEL * 0.55),
            medidas::FILA_CONTENIDO_PANEL
        ),
        font, sf::Color::Black, 0.7
    );

    reiniciar = crearBotonConTexto(
        "Reiniciar", sf::Color::Blue,
        sf::Vector2i(1440, medidas::FILA_BOTONES_GENERALES), font
    );
    salir = crearBotonConTexto(
        "Salir", sf::Color::Red,
        sf::Vector2i(1640, medidas::FILA_BOTONES_GENERALES), font
    );

    todos = {&empezar, &encargar_margarita, &despachar, &reiniciar, &salir};
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
    int pos_x =
        obtener_posicion_x_panel(indice_panel) + medidas::MARGEN_IZQ_ETIQUETAS;
    int pos_y = medidas::FILA_TITULOS_PANELES;
    etiqueta.setPosition(pos_x, pos_y);
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
        medidas::FILA_CONTENIDO_PANEL
    );
    return etiqueta;
}
sf::Text crearEtiquetaPizzasPreparadas(const sf::Font &font) {
    sf::Text etiqueta =
        crearEtiqueta(medidas::TAMANO_FUENTE_ETIQUETAS, font, sf::Color::White);
    auto pos_x = obtener_posicion_x_panel(PANEL_PREPARADAS) +
                 medidas::MARGEN_IZQ_ETIQUETAS;
    etiqueta.setPosition(pos_x, medidas::FILA_CONTENIDO_PANEL);
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
    encargar = crear_panel_estandar(PANEL_ENCARGAR);
    en_preparacion = crear_panel_estandar(PANEL_EN_PREPARACION);
    preparadas = crear_panel_estandar(PANEL_PREPARADAS);
    pedidos = crear_panel_estandar(PANEL_PEDIDOS);
}

void Paneles::dibujar(sf::RenderWindow &window) {
    window.draw(encargar);
    window.draw(en_preparacion);
    window.draw(preparadas);
    window.draw(pedidos);
}

std::vector<BarraProgresoConNombre> crear_visualizaciones_porcentajes(
    const std::vector<int> &porcentajes,
    const std::vector<std::string> &nombres, sf::Font &font
) {
    assert(porcentajes.size() == nombres.size());
    std::vector<BarraProgresoConNombre> vect{};
    int i = 0;
    int pos_x = obtener_posicion_x_panel(PANEL_EN_PREPARACION) +
                medidas::MARGEN_IZQ_ETIQUETAS;
    int pos_y_inicial = medidas::FILA_CONTENIDO_PANEL;
    int ancho = 300;
    int largo = 40;
    for (auto porcentaje : porcentajes) {
        BarraProgresoConNombre bpn;
        BarraProgreso &bp = bpn.bp;
        bp.fondo = sf::RectangleShape(sf::Vector2f(ancho, largo));
        bp.relleno =
            sf::RectangleShape(sf::Vector2f(ancho * porcentaje / 100, largo));
        bp.fondo.setFillColor(sf::Color(COLOR_BARRA_PROGRESO_FONDO));
        bp.relleno.setFillColor(sf::Color(COLOR_BARRA_PROGRESO_RELLENO));
        int offset_y = i * medidas::DIFERENCIA_VERTICAL_ENTRE_BARRAS_PROGRESO;
        int pos_y = pos_y_inicial + offset_y;
        bp.fondo.setPosition(pos_x, pos_y);
        bp.relleno.setPosition(pos_x, pos_y);
        bpn.etiqueta = sf::Text(nombres[i], font, 24);
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
        crearEtiquetaTituloPanel(font, IndicePanel::PANEL_ENCARGAR, "Encargar"),
        crearEtiquetaTituloPanel(
            font, IndicePanel::PANEL_EN_PREPARACION, "En preparaci%on"
        ),
        crearEtiquetaTituloPanel(
            font, IndicePanel::PANEL_PREPARADAS, "Preparadas"
        ),
        crearEtiquetaTituloPanel(font, IndicePanel::PANEL_PEDIDOS, "Pedidos")};
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
        ventana.draw(tpv.bp.fondo);
        ventana.draw(tpv.bp.relleno);
        ventana.draw(tpv.etiqueta);
    }
}
