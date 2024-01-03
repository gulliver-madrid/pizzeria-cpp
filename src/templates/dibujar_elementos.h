#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <map>

template <typename Key, typename Drawable>
void dibujar_elementos(
    sf::RenderWindow &ventana,               //
    const std::map<Key, Drawable> &elementos //
) {
    for (const auto &[_, elemento] : elementos) {
        ventana.draw(elemento);
    }
}

template <typename Drawable>
void dibujar_elementos(
    sf::RenderWindow &ventana, const std::vector<Drawable> &elementos
) {
    for (const auto &elemento : elementos) {
        ventana.draw(elemento);
    }
}

template <typename... Drawables>
void dibujar_elementos(
    sf::RenderWindow &ventana, const std::tuple<Drawables...> &drawables
) {
    std::apply(
        [&ventana](const auto &...drawable) { //
            (ventana.draw(drawable), ...);
        },
        drawables
    );
}
