#include "componente.h"

using ComponentePtr = std::shared_ptr<Componente>;

namespace {
    /* Anade la fuente si el componente es componente con font */
    void try_to_add_font(ComponentePtr &comp, OptionalFont &font) {
        auto comp_f = std::dynamic_pointer_cast<ComponenteConPosibleFont>(comp);
        if (comp_f) {
            comp_f->set_font(font);
        }
    }
} // namespace

///////////////////////////////////////////
// Componente (public)
//////////////////////////////////////////

void Componente::add_child(ComponentePtr child) { //
    children.push_back(child);
}

std::vector<ComponentePtr> Componente::get_children() const { return children; }

///////////////////////////////////////////
// ComponenteConPosibleFont (public)
//////////////////////////////////////////

void ComponenteConPosibleFont::add_child(ComponentePtr child) {
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
