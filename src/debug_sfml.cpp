#include "debug_sfml.h"

void debug_rect(sf::RectangleShape &rect, std::string name) {
    std::cout << name << ".getPosition(): " << rect.getPosition().x << ", "
              << rect.getPosition().y << std::endl;
    std::cout << name << ".getLocalBounds(): " << rect.getLocalBounds().left
              << ", " << rect.getLocalBounds().top << std::endl;
    std::cout << name << ".getGlobalBounds(): " << rect.getGlobalBounds().left
              << ", " << rect.getGlobalBounds().top << ", "
              << rect.getGlobalBounds().width << ", "
              << rect.getGlobalBounds().height << std::endl;
}

void debug_float_rect(sf::FloatRect rect) {
    std::cout << "getPosition(): " << rect.getPosition().x << ", "
              << rect.getPosition().y << std::endl;
    std::cout << "left: " << rect.left << std::endl;
    std::cout << "top: " << rect.top << std::endl;
    std::cout << "width: " << rect.width << std::endl;
    std::cout << "height: " << rect.height << std::endl;
    std::cout << std::endl;
}
