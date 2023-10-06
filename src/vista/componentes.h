#pragma once

#include "../globales.h"
#include <SFML/Window.hpp>
#include <optional>

struct BotonConTexto {
    sf::RectangleShape boton;
    sf::Text texto;
    bool activo = true;
    bool visible = false;
    sf::Sound sound;

    BotonConTexto();
    BotonConTexto(sf::RectangleShape rectShape, sf::Text txt);
    bool colisiona(const sf::Vector2i &mousePos, const Globales &globales);
    void dibujar(sf::RenderWindow &window);
    void activar();
    void desactivar();
    void activacion_condicional(bool condicion);

  private:
    std::optional<sf::Color> colorBotonActivo;
};

struct FuenteTexto {
    const int tamano;
    const sf::Color &color;
    const sf::Font &font;
};

const auto VECTOR_CERO = sf::Vector2f(0, 0);

sf::Text crearEtiqueta(
    int, const sf::Font &, const sf::Color &,
    const sf::Vector2f &posicion = VECTOR_CERO
);
sf::Text crearEtiqueta(
    const FuenteTexto &fuente_texto, const sf::Vector2f &posicion = VECTOR_CERO
);
