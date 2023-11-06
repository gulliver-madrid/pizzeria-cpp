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
    static size_t _proximo_id;
    std::optional<size_t> _id;

    sf::RectangleShape _forma;
    sf::Text _etiqueta;

    std::unique_ptr<Posicionamiento> posicionamiento;
    double _escala = 1;
    bool _activo = true;

    void _asignar_id();
    void _calcular_posicion_absoluta();
    BotonConTexto();

  public:
    bool visible = false;
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

    // Eliminamos operadores de copia y asignacion
    BotonConTexto(const BotonConTexto &) = delete;
    BotonConTexto &operator=(const BotonConTexto &) = delete;

    // Creamos los operadores de movimiento y asignacion de movimiento
    // por defecto
    BotonConTexto(BotonConTexto &&otro) noexcept;
    BotonConTexto &operator=(BotonConTexto &&) noexcept;

    ~BotonConTexto();

    void establecer_rect_padre(const sf::FloatRect &);

    /* Establece la posicion relativa */
    void establecer_posicion(
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
    sf::FloatRect get_rect() const { //
        return _forma.getGlobalBounds();
    }

  private:
    std::optional<sf::Color> colorBotonActivo;
};
