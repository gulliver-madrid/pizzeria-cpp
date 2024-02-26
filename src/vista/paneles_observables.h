#pragma once

#include <SFML/System/Vector2.hpp>

enum class IndicePanel;

///////////////////////////////////////////
// PanelesObservables
/////////////////////////////////////////

class PanelesObservables {
  public:
    virtual bool get_visibilidad() const = 0;
    virtual bool colisiona(IndicePanel, const sf::Vector2i &) const = 0;
};
