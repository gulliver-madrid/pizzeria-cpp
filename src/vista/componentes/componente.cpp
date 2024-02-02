#include "componente.h"

namespace {
    /* Anade la fuente si el componente es componente con font */
    void try_to_add_font(ComponenteSharedPtr &comp, OptionalFont &font) {
        auto comp_f = std::dynamic_pointer_cast<ComponenteConFont>(comp);
        if (comp_f) {
            comp_f->set_font(font);
        }
    }
} // namespace

///////////////////////////////////////////
// Componente (public)
//////////////////////////////////////////

void Componente::add_child(ComponenteSharedPtr child) { //
    assert(child);
    children.push_back(child);
}
void Componente::remove_child(ComponenteSharedPtr child) { //
    assert(child);
    children.erase(
        std::remove_if(
            children.begin(), children.end(),
            [&child](const ComponenteSharedPtr &comp) { return comp == child; }
        ),
        children.end()
    );
}

std::vector<ComponenteSharedPtr> Componente::get_children() const {
    return children;
}

///////////////////////////////////////////
// ComponenteConFont (public)
//////////////////////////////////////////

void ComponenteConFont::add_child(ComponenteSharedPtr child) {
    if (font.exists()) {
        try_to_add_font(child, font);
    }
    Componente::add_child(child);
}

void ComponenteConFont::set_font(const OptionalFont &new_font) {
    // Solo actualiza la fuente si se aporta una nueva fuente
    // Pero no si esta viene vacia
    if (!new_font.exists()) {
        return;
    };
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
