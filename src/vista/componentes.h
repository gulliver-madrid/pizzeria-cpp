#pragma once

#include "../general.h"
#include <SFML/Graphics.hpp>
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
    bool colisiona(sf::Vector2i &mousePos, Globales &globales);
    void dibujar(sf::RenderWindow &window);
    void activar();
    void desactivar();

  private:
    std::optional<sf::Color> colorBotonActivo;
};

sf::Text crearEtiqueta(int, const sf::Font &, const sf::Color &);
