#pragma once

#include <SFML/Graphics.hpp>
#include <optional>

struct Timer {
  private:
    std::optional<sf::Clock> clock;
    float finalizacion = 0;
    float get_seconds();

  public:
    void start(float finalizacion);
    bool termino();
};
