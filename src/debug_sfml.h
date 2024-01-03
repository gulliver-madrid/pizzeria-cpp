#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <iostream>
#include <string>

namespace sf {
    class RectangleShape;
}

namespace debug {
    void debug_rect(sf::RectangleShape &rect, std::string name);
    void debug_float_rect(sf::FloatRect rect);
} // namespace debug

/*
 * Crea una representacion de los pares de un contenedor iterable, suponiendo
 * que sus elementos puedan usarse con std::cout
 */
template <typename Iterable> void debug_pares(const Iterable &contenedor) {
    using namespace std;
    cout << "[";
    for (const auto &[primero, segundo] : contenedor) {
        cout << "(" << primero << ", " << segundo << "), ";
    }
    cout << "]" << endl;
}
