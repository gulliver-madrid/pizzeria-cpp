#pragma once

#include <SFML/Graphics.hpp>

class FabricaEtiquetasContadores {
  private:
    static sf::Vector2f _obtener_posicion_etiqueta_contador_pizzas(
        const sf::Vector2f pos_panel, size_t indice_etiqueta,
        int desplazamiento_vertical
    );

    static sf::Text _crearEtiquetaContadorPizzas(
        sf::Vector2f posicion_panel, //
        size_t indice_etiqueta,      //
        int desplazamiento_vertical, //
        const sf::Font &font         //
    );

  public:
    static sf::Text
    crearEtiquetaPizzasPreparadas(const sf::Font &font, size_t indice_etiqueta);

    static sf::Text
    crearEtiquetaPizzasServidas(const sf::Font &font, size_t indice_etiqueta);
};
