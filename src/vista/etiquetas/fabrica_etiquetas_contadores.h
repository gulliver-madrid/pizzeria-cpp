#pragma once

#include <SFML/Graphics.hpp>

class FabricaEtiquetasContadores {
  private:
    const sf::Font &font;
    sf::Vector2f _obtener_posicion_etiqueta_contador_pizzas(
        const sf::Vector2f pos_panel, //
        size_t indice_etiqueta,       //
        int desplazamiento_vertical   //
    ) const;

    sf::Text _crearEtiquetaContadorPizzas(sf::Vector2f posicion) const;

  public:
    FabricaEtiquetasContadores(const sf::Font &font) : font(font){};
    sf::Text crearEtiquetaPizzasPreparadas(size_t indice_etiqueta) const;
    sf::Text crearEtiquetaPizzasServidas(size_t indice_etiqueta) const;
};
