#include "visual.h"
#include "../debug.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>

#define FPS 16
#define ORANGE 255, 128, 0

int demo_visual() {
    sf::RenderWindow window;
    window.create(sf::VideoMode(1800, 920), "Demo visual");
    window.setFramerateLimit(FPS);
    sf::RectangleShape yellow_rect(sf::Vector2f(50, 50));
    yellow_rect.setFillColor(sf::Color::Yellow);
    yellow_rect.setPosition(100, 100);
    debug_rect(yellow_rect, "yellow_rect");

    sf::RectangleShape blue_rect(sf::Vector2f(300, 900));
    blue_rect.setFillColor(sf::Color::Blue);
    blue_rect.setPosition(600, 50);

    sf::RectangleShape green_rect(sf::Vector2f(300, 900));
    green_rect.setFillColor(sf::Color::Green);
    green_rect.setPosition(900, 50);

    sf::RectangleShape last_rect(sf::Vector2f(300, 900));
    last_rect.setFillColor(sf::Color(ORANGE));
    last_rect.setPosition(1200, 50);

    sf::RectangleShape red_rect(sf::Vector2f(50, 50));
    red_rect.setFillColor(sf::Color::Red);
    int i = 0;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        red_rect.setPosition(100 + i * 10, 400);
        window.draw(yellow_rect);
        window.draw(blue_rect);
        window.draw(last_rect);
        window.draw(red_rect);
        window.draw(green_rect);
        window.display();
        i++;
    }
    return 0;
}
