#include "componentes.h"

/*
 * Solo se detectará la colisión si el botón está visible y activo
 */
bool BotonConTexto::colisiona(
    const sf::Vector2i &mousePos, const Globales &globales
) {
    if (!visible || !activo)
        return false;
    bool colisiona = boton.getGlobalBounds().contains(
        static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)
    );
    if (!colisiona) {
        return false;
    }
    if (globales.button_click_buffer) {
        sound.setBuffer(globales.button_click_buffer.value());
        sound.play();
    }
    return true;
}

void BotonConTexto::dibujar(sf::RenderWindow &window) {
    if (!visible)
        return;
    if (!colorBotonActivo.has_value())
        colorBotonActivo = boton.getFillColor();
    if (activo) {
        boton.setFillColor(colorBotonActivo.value());
    } else {
        boton.setFillColor(sf::Color(100, 100, 100));
    }
    window.draw(boton);
    window.draw(texto);
}

BotonConTexto::BotonConTexto(sf::RectangleShape rectShape, sf::Text txt)
    : boton(rectShape), texto(txt) {
    colorBotonActivo = boton.getFillColor();
    boton.setOutlineColor(sf::Color::Black);
    boton.setOutlineThickness(2);
};
BotonConTexto::BotonConTexto(){};

sf::Text
crearEtiqueta(int tamano, const sf::Font &font, const sf::Color &color) {
    // Usamos un placeholder para poder obtener la altura
    sf::Text etiqueta("<Placeholder>", font, tamano);
    etiqueta.setFillColor(color);
    return etiqueta;
}

/**
 * Activa el botón solo si está actualmente inactivo.
 */
void BotonConTexto::activar() {
    if (!activo)
        activo = true;
}

/**
 * Desactiva el botón solo si está actualmente activo.
 */
void BotonConTexto::desactivar() {
    if (activo)
        activo = false;
}
