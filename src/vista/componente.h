#pragma once

#include "../shared/font.h"
#include <SFML/Graphics/Drawable.hpp>
#include <cassert>
#include <memory>
#include <vector>

class Componente;
using ComponentePtr = std::shared_ptr<Componente>;

///////////////////////////////////////////
// Componente
//////////////////////////////////////////

class Componente : public sf::Drawable {
  protected:
    std::vector<ComponentePtr> children;

  public:
    virtual ~Componente() = default;
    virtual void add_child(ComponentePtr child);
    std::vector<ComponentePtr> get_children() const;
};

///////////////////////////////////////////
// ComponenteConFont
//////////////////////////////////////////

class ComponenteConFont : public Componente, public ObjetoConFont {
  public:
    virtual void add_child(ComponentePtr child) override;
    virtual void set_font(const OptionalFont &new_font) override;
};
