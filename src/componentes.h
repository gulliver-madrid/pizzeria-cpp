#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <optional>

struct BotonConTexto {
    sf::RectangleShape boton;
    sf::Text texto;
    bool activo = true;
    bool visible = false;

    BotonConTexto();
    BotonConTexto(sf::RectangleShape rectShape, sf::Text txt);
    bool colisiona(sf::Vector2i &mousePos);
    void dibujar(sf::RenderWindow &window);
    void activar();
    void desactivar();

  private:
    std::optional<sf::Color> colorBotonActivo;
};

sf::Text crearEtiqueta(int, const sf::Font &, const sf::Color &);
