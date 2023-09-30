#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <optional>

struct Globales {
    sf::RenderWindow window;
    sf::Font font;
    std::optional<sf::SoundBuffer> success_buffer;
    std::optional<sf::SoundBuffer> button_click_buffer;
    sf::Music music;
};
