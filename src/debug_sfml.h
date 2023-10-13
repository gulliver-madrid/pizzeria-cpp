#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

namespace debug {
    void debug_rect(sf::RectangleShape &rect, std::string name);
    void debug_float_rect(sf::FloatRect rect);
} // namespace debug

/* Crea una representacion de los pares de un contenedor iterable, suponiendo
 * que sus elementos puedan usarse con std::cout
 */
template <typename Iterable> void debug_pares(const Iterable &contenedor) {
    std::cout << "[";
    for (const auto &par : contenedor) {
        std::cout << "(" << par.first << ", " << par.second << "), ";
    }
    std::cout << "]" << std::endl;
}
