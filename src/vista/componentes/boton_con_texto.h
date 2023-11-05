#pragma once

#include "boton_data.h"
#include "componente.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <optional>

class BotonConTexto : public Componente {
  private:
    static size_t proximo_id;
    std::optional<size_t> _id;
    bool activo = true;
    sf::RectangleShape forma;
    sf::Text etiqueta;
    double escala = 1;
    sf::FloatRect _rect_padre;
    sf::Vector2f _posicion_relativa;
    Align _alineamiento = Align::Left;

    void asignar_id();
    void _calcular_posicion_absoluta();

  public:
    bool visible = false;
    BotonConTexto();
    BotonConTexto(sf::RectangleShape rectShape, sf::Text txt);
    BotonConTexto(
        const BotonData &boton_data, //
        const sf::Font &font,        //
        double escala = 1            //
    );
    BotonConTexto(
        const BotonData &boton_data,  //
        const sf::Vector2f &posicion, //
        const sf::Font &font,         //
        Align align = Align::Left,    //
        double escala = 1             //
    );

    void establecer_rect_padre(const sf::FloatRect &);

    /* Establece la posicion relativa */
    void establecerPosicion(
        const sf::Vector2f &posicion, //
        const Align align = Align::Left
    );
    bool colisiona(const sf::Vector2i &mousePos) const;
    void dibujar(sf::RenderWindow &window);
    void activar();
    void desactivar();
    void activacion_condicional(bool condicion);
    size_t get_id() const;
    bool esta_activo() const;
    sf::FloatRect getGlobalBounds() const { //
        return forma.getGlobalBounds();
    }

  private:
    std::optional<sf::Color> colorBotonActivo;
};
