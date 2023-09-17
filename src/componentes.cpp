#include "componentes.h"

bool BotonConTexto::colisiona(sf::Vector2i &mousePos) {
    if (!this->visible || !this->activo)
        return false;
    return boton.getGlobalBounds().contains(
        static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)
    );
}

void BotonConTexto::dibujar(sf::RenderWindow &window) {
    if (visible) {
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
}

BotonConTexto::BotonConTexto(sf::RectangleShape rectShape, sf::Text txt)
    : boton(rectShape), texto(txt) {
    colorBotonActivo = boton.getFillColor();
};
BotonConTexto::BotonConTexto(){};
