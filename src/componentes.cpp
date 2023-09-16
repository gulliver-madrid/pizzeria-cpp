#include "componentes.h"

bool BotonConTexto::colisiona(sf::Vector2i &mousePos) {
    if (!this->activo)
        return false;
    return boton.getGlobalBounds().contains(
        static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)
    );
}

void BotonConTexto::dibujar(sf::RenderWindow &window) {
    window.draw(boton);
    window.draw(texto);
}
