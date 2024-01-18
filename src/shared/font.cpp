#include "font.h"
#include <SFML/Graphics/Font.hpp>
#include <cassert>
#include <memory>
#include <optional>

void OptionalFont::set_pointer(std::shared_ptr<sf::Font> ptr) { //
    font_ptr = ptr;
}

std::shared_ptr<sf::Font> OptionalFont::get_pointer() const { //
    assert(exists());
    return font_ptr;
}

bool OptionalFont::exists() const { //
    return font_ptr != nullptr;
}

ObjetoConFont::ObjetoConFont() {}
ObjetoConFont::ObjetoConFont(const OptionalFont &font) : font(font) {}
