#pragma once

#include "boton_data.h"
#include "componente.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <memory>
#include <optional>

struct Posicionamiento;

class BotonConTexto : public Componente {
  private:
    static size_t proximo_id;
    std::optional<size_t> _id;
    bool activo = true;
    sf::RectangleShape forma;
    sf::Text etiqueta;
    std::unique_ptr<Posicionamiento> posicionamiento;
    double escala = 1;
    void asignar_id();
    void _calcular_posicion_absoluta();

  public:
    bool visible = false;
    BotonConTexto();
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
    BotonConTexto(const BotonConTexto &) = delete;
    BotonConTexto &operator=(const BotonConTexto &) = delete;
    BotonConTexto(BotonConTexto &&otro) noexcept;
    BotonConTexto &operator=(BotonConTexto &&) noexcept;

    ~BotonConTexto();

    void establecer_rect_padre(const sf::FloatRect &);

    /* Establece la posicion relativa */
    void establecerPosicion(
        const sf::Vector2f &posicion, //
        Align align = Align::Left
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
