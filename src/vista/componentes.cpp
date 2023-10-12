#include "componentes.h"

size_t BotonConTexto::proximo_id = 0;

/*
 * Solo se detectará la colisión si el botón está visible y activo
 */
bool BotonConTexto::colisiona(const sf::Vector2i &mousePos) const {
    if (!visible || !activo)
        return false;
    return forma.getGlobalBounds().contains(
        static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)
    );
}

void BotonConTexto::dibujar(sf::RenderWindow &window) {
    if (!visible)
        return;
    if (!colorBotonActivo.has_value())
        colorBotonActivo = forma.getFillColor();
    if (activo) {
        forma.setFillColor(colorBotonActivo.value());
    } else {
        forma.setFillColor(sf::Color(100, 100, 100));
    }
    window.draw(forma);
    window.draw(etiqueta);
}

BotonConTexto::BotonConTexto(sf::RectangleShape rectShape, sf::Text txt)
    : forma(rectShape), etiqueta(txt) {
    colorBotonActivo = forma.getFillColor();
    forma.setOutlineColor(sf::Color::Black);
    forma.setOutlineThickness(2);
    id = proximo_id++;
};

BotonConTexto::BotonConTexto(){};

sf::Text crearEtiqueta(
    int tamano, const sf::Font &font, const sf::Color &color,
    const sf::Vector2f &posicion
) {
    // Usamos un placeholder para poder obtener la altura
    sf::Text etiqueta("<Placeholder>", font, tamano);
    etiqueta.setFillColor(color);
    etiqueta.setPosition(posicion);
    return etiqueta;
}

/* Sobrecarga para usar FuenteTexto */
sf::Text
crearEtiqueta(const FuenteTexto &fuente_texto, const sf::Vector2f &posicion) {
    return crearEtiqueta(
        fuente_texto.tamano, fuente_texto.font, fuente_texto.color, posicion
    );
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

void BotonConTexto::activacion_condicional(bool condicion) {
    if (condicion) {
        activar();
    } else {
        desactivar();
    }
}
size_t BotonConTexto::get_id() const { //
    return id;
}

bool BotonConTexto::esta_activo() const { //
    return activo;
}
