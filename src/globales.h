#pragma once

#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <optional>

namespace sf {
    class Sound;
}

struct BotonConTexto;

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
