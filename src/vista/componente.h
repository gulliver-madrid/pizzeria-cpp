#pragma once

#include "../shared/font.h"
#include <cassert>
#include <memory>
#include <vector>

class Componente {

  public:
    std::vector<std::shared_ptr<Componente>> children;
    // Indica si es un componente con posible font
    bool has_font;

    virtual ~Componente() = default;
    void add_child(std::shared_ptr<Componente> child) {
        children.push_back(child);
    }
};

class ComponenteConPosibleFont : public Componente {
  public:
    OptionalFont font;
    ComponenteConPosibleFont() { //
        has_font = true;
    };
    void add_child(std::shared_ptr<ComponenteConPosibleFont> child) {
        if (font.exists()) {
            child->font = font;
        }
        Componente::add_child(child);
    }
    void set_font(OptionalFont &new_font) {
        if (font.get_pointer() != new_font.get_pointer()) {
            font = new_font;
        }
        for (auto child : children) {
            if (child->has_font) {
                std::shared_ptr<ComponenteConPosibleFont> child_con_font =
                    std::dynamic_pointer_cast<ComponenteConPosibleFont>(child);
                assert(child_con_font);
                child_con_font->set_font(font);
            }
        }
    }
};
