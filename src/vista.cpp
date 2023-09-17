#include "vista.h"
#include <cassert>

#define TAMANO_FUENTE_ETIQUETAS 48
#define MARGEN_IZQ_ETIQUETAS 50

sf::Text crearEtiqueta(int tamano, sf::Font &font, sf::Color color) {
    // Usamos un placeholder para poder obtener la altura
    sf::Text etiqueta("<Placeholder>", font, tamano);
    etiqueta.setFillColor(color);
    return etiqueta;
}

// Crea un botón rectangular con texto
BotonConTexto crearBotonConTexto(
    std::string texto, sf::Color color_fondo, sf::Vector2i posicion,
    sf::Font &font, sf::Color color_texto
) {
    int tamano_texto = 24;
    int x = posicion.x;
    int y = posicion.y;
    int margin = 25;

    // Primero creamos la etiqueta para usar sus límites en el Rect
    sf::Text etiqueta = crearEtiqueta(tamano_texto, font, color_texto);
    etiqueta.setString(texto);
    etiqueta.setPosition(x + margin, y + margin);
    sf::FloatRect textRect = etiqueta.getGlobalBounds();

    // Rect
    sf::RectangleShape rect(
        sf::Vector2f(textRect.width + margin * 2, textRect.height + margin * 2)
    );
    rect.setFillColor(color_fondo);
    rect.setPosition(x, y);

    return BotonConTexto(rect, etiqueta);
};

Botones::Botones(sf::Font &font, int pos_y_bajo_etiquetas) {
    int filaBotonesEjecutivos = pos_y_bajo_etiquetas + 50;
    int bottom = 800;

    auto botonEmpezar = crearBotonConTexto(
        "Empezar", sf::Color::Green, sf::Vector2i(500, 450), font,
        sf::Color::Black
    );
    auto botonEncargar = crearBotonConTexto(
        "Encargar pizza", sf::Color::Green,
        sf::Vector2i(50, filaBotonesEjecutivos), font, sf::Color::Black
    );
    auto botonDespachar = crearBotonConTexto(
        "Despachar pizza", sf::Color::Green,
        sf::Vector2i(300, filaBotonesEjecutivos), font, sf::Color::Black
    );

    auto botonReiniciar = crearBotonConTexto(
        "Reiniciar", sf::Color::Blue, sf::Vector2i(150, bottom), font
    );
    auto botonSalir = crearBotonConTexto(
        "Salir", sf::Color::Red, sf::Vector2i(400, bottom), font
    );
    empezar = botonEmpezar;
    encargar = botonEncargar;
    despachar = botonDespachar;
    reiniciar = botonReiniciar;
    salir = botonSalir;
    todos = {&empezar, &encargar, &despachar, &reiniciar, &salir};
    assert(todos.size() == 5);
}

// Crea la etiqueta de texto que mostrará el contador
sf::Text crearEtiquetaContador(sf::Font &font) {
    sf::Text etiqueta =
        crearEtiqueta(TAMANO_FUENTE_ETIQUETAS, font, sf::Color::White);
    etiqueta.setPosition(MARGEN_IZQ_ETIQUETAS, 50);
    return etiqueta;
}
sf::Text crearEtiquetaPizzasPreparadas(sf::Font &font, float prev_position) {
    sf::Text etiqueta =
        crearEtiqueta(TAMANO_FUENTE_ETIQUETAS, font, sf::Color::White);
    auto pos_x = MARGEN_IZQ_ETIQUETAS;
    auto pos_y = prev_position + font.getLineSpacing(TAMANO_FUENTE_ETIQUETAS);
    etiqueta.setPosition(pos_x, pos_y);
    return etiqueta;
}
