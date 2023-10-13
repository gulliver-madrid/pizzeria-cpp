#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <optional>

struct BotonConTexto {
  private:
    static size_t proximo_id;
    size_t id;
    bool activo = true;
    sf::RectangleShape forma;
    sf::Text etiqueta;

  public:
    bool visible = false;
    BotonConTexto();
    BotonConTexto(sf::RectangleShape rectShape, sf::Text txt);
    bool colisiona(const sf::Vector2i &mousePos) const;
    void dibujar(sf::RenderWindow &window);
    void activar();
    void desactivar();
    void activacion_condicional(bool condicion);
    size_t get_id() const;
    bool esta_activo() const;
    sf::FloatRect getGlobalBounds() const { //
        return forma.getGlobalBounds();
    }

  private:
    std::optional<sf::Color> colorBotonActivo;
};
