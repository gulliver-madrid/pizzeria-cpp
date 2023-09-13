#include "unicode.h"
#include <SFML/Graphics.hpp>

#define DEMO_UNICODE_FONT_PATH "C:\\Windows\\Fonts\\arial.ttf"

int demo_unicode() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

    sf::Font font;

    if (!font.loadFromFile(DEMO_UNICODE_FONT_PATH)) {
        return EXIT_FAILURE;
    }

    sf::Text text;
    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text.setString(L"Algunos carácteres: ¡ñáéíóú");
    text.setCharacterSize(24);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(text);
        window.display();
    }

    return 0;
}
