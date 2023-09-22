#include "debug.h"

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
