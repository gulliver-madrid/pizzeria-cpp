#pragma once

#include <SFML/Graphics/Text.hpp>

class Etiqueta;

class FabricaEtiquetasPreparadas {
  private:
    sf::Vector2f _obtener_posicion_etiqueta(
        sf::Vector2f pos_panel,       //
        size_t indice_etiqueta,       //
        float desplazamiento_vertical //
    ) const;

    std::shared_ptr<Etiqueta> _crear_etiqueta(sf::Vector2f posicion) const;

  public:
    std::shared_ptr<Etiqueta>
    crearEtiquetaPizzasPreparadas(size_t indice_etiqueta) const;
};
