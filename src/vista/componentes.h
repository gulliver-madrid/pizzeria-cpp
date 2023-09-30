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

  private:
    std::optional<sf::Color> colorBotonActivo;
};

sf::Text crearEtiqueta(int, const sf::Font &, const sf::Color &);
