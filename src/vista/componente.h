#pragma once

#include "../shared/font.h"
#include <cassert>
#include <memory>
#include <vector>

///// Componente /////

class Componente {

  public:
    std::vector<std::shared_ptr<Componente>> children;
    // Indica si es un componente con posible font
    bool has_font = false;

    virtual ~Componente() = default;
    virtual void add_child(std::shared_ptr<Componente> child);
};

///// ComponenteConPosibleFont /////

class ComponenteConPosibleFont : public Componente {
  public:
    OptionalFont font;
    ComponenteConPosibleFont();
    virtual void add_child(std::shared_ptr<Componente> child) override;
    void set_font(OptionalFont &new_font);
};
