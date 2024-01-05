#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <map>

template <typename Key, typename Drawable>
void dibujar_elementos(
    sf::RenderTarget &(target),              //
    const std::map<Key, Drawable> &elementos //
) {
    for (const auto &[_, elemento] : elementos) {
        target.draw(elemento);
    }
}

template <typename Drawable>
void dibujar_elementos(
    sf::RenderTarget &(target), const std::vector<Drawable> &elementos
) {
    for (const auto &elemento : elementos) {
        target.draw(elemento);
    }
}

template <typename... Drawables>
void dibujar_elementos(
    sf::RenderTarget &(target), const std::tuple<Drawables...> &drawables
) {
    std::apply(
        [&target](const auto &...drawable) { //
            (target.draw(drawable), ...);
        },
        drawables
    );
}
