#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <map>
#include <tuple>
#include <vector>

// template <typename Key, typename Drawable>
// void dibujar_elementos(
//     sf::RenderTarget &target,                                 //
//     const std::map<Key, std::unique_ptr<Drawable>> &elementos //
// ) {
//     for (const auto &[_, elemento] : elementos) {
//         target.draw(*elemento);
//     }
// }

template <typename Key, typename Drawable>
void dibujar_elementos(
    sf::RenderTarget &target,                                 //
    const std::map<Key, std::unique_ptr<Drawable>> &elementos //
) {
    for (const auto &[_, elemento] : elementos) {
        if (elemento) {
            target.draw(*elemento);
        }
    }
}

template <typename Key, typename Drawable>
void dibujar_elementos(
    sf::RenderTarget &target,                //
    const std::map<Key, Drawable> &elementos //
) {
    for (const auto &[_, elemento] : elementos) {
        target.draw(elemento);
    }
}

template <typename Drawable>
void dibujar_elementos(
    sf::RenderTarget &target, const std::vector<Drawable> &elementos
) {
    for (const auto &elemento : elementos) {
        target.draw(elemento);
    }
}

template <typename... Drawables>
void dibujar_elementos(
    sf::RenderTarget &target, const std::tuple<Drawables...> &drawables
) {
    std::apply(
        [&target](const auto &...drawable) { //
            (target.draw(drawable), ...);
        },
        drawables
    );
}
