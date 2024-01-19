#include "componente.h"

namespace {
    /* Anade la fuente si el componente es componente con font */
    void try_to_add_font(
        std::shared_ptr<Componente> &componente, OptionalFont &font
    ) {
        auto componente_con_font =
            std::dynamic_pointer_cast<ComponenteConPosibleFont>(componente);
        if (componente_con_font) {
            componente_con_font->set_font(font);
        }
    }
} // namespace

///// Componente /////

void Componente::add_child(std::shared_ptr<Componente> child) {
    children.push_back(child);
}

std::vector<std::shared_ptr<Componente>> Componente::get_children() const {
    return children;
}

///// ComponenteConPosibleFont /////

void ComponenteConPosibleFont::add_child(std::shared_ptr<Componente> child) {
    if (font.exists()) {
        try_to_add_font(child, font);
    }
    Componente::add_child(child);
}

void ComponenteConPosibleFont::set_font(OptionalFont &new_font) {
    assert(new_font.exists());
    if (                                               //
        !font.exists() ||                              //
        (font.get_pointer() != new_font.get_pointer()) //
    ) {
        font = new_font;
    }
    for (auto child : children) {
        try_to_add_font(child, font);
    }
}
