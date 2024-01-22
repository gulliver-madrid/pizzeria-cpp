#pragma once

#include "../shared/font.h"
#include <SFML/Graphics/Drawable.hpp>
#include <cassert>
#include <memory>
#include <vector>

class Componente;
using ComponenteSharedPtr = std::shared_ptr<Componente>;

///////////////////////////////////////////
// Componente
//////////////////////////////////////////

class Componente : public sf::Drawable {
  protected:
    std::vector<ComponenteSharedPtr> children;

  public:
    virtual ~Componente() = default;
    virtual void add_child(ComponenteSharedPtr child);
    virtual void remove_child(ComponenteSharedPtr child);
    std::vector<ComponenteSharedPtr> get_children() const;
};

///////////////////////////////////////////
// ComponenteConFont
//////////////////////////////////////////

class ComponenteConFont : public Componente, public ObjetoConFont {
  public:
    virtual void add_child(ComponenteSharedPtr child) override;
    virtual void set_font(const OptionalFont &new_font) override;
};
