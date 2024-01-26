#pragma once

#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include <optional>

namespace sf {
    class Sound;
}

class BotonConTexto;

class Globales {
  private:
    std::map<size_t, sf::Sound> sounds;

  public:
    sf::RenderWindow window;
    std::shared_ptr<sf::Font> font = std::make_shared<sf::Font>();
    std::optional<sf::SoundBuffer> success_buffer;
    std::optional<sf::SoundBuffer> button_click_buffer;
    sf::Music music;
    bool detecta_colision(
        std::shared_ptr<BotonConTexto> boton, const sf::Vector2i &mouse_pos
    );
};
