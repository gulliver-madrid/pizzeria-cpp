#pragma once

#include "vista/componentes.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>

struct Globales {
  private:
    std::map<int, sf::Sound> sounds;

  public:
    sf::RenderWindow window;
    sf::Font font;
    std::optional<sf::SoundBuffer> success_buffer;
    std::optional<sf::SoundBuffer> button_click_buffer;
    sf::Music music;
    bool
    detecta_colision(const BotonConTexto &boton, const sf::Vector2i &mouse_pos);
};
