#pragma once

#include "../componente.h"
#include "boton_data.h"
#include "componente_old_style.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <memory>
#include <optional>

class Etiqueta;

namespace sf {
    class RenderTarget;
}

struct Posicionamiento;

///////////////////////////////////////////
// BotonConTexto
//////////////////////////////////////////

class BotonConTexto : public ComponenteOldStyle, public ComponenteConFont {
  private:
    static size_t _proximo_id;
    std::optional<size_t> _id;

    sf::RectangleShape _forma;
    std::shared_ptr<Etiqueta> _etiqueta;

    // TODO: ver si es necesario
    sf::Color _color_fondo = sf::Color::White;

    std::unique_ptr<Posicionamiento> posicionamiento;
    // Solo puede modificarse la escala en la construccion
    double _escala = 1;
    bool _activo = true;
    std::optional<sf::Color> colorBotonActivo;

    BotonConTexto();
    void _asignar_id();
    void _actualizar_posicion_absoluta();
    void _resize();
    int BotonConTexto::get_margen_ambos_lados();

  public:
    bool visible = false;
    BotonConTexto(
        const BotonData boton_data, //
        double escala = 1           //
    );
    BotonConTexto(
        const BotonData boton_data,   //
        const sf::Vector2f &posicion, //
        Align align = Align::Left,    //
        double escala = 1             //
    );

    // Eliminamos operadores de copia y asignacion
    BotonConTexto(const BotonConTexto &) = delete;
    BotonConTexto &operator=(const BotonConTexto &) = delete;

    // Creamos los operadores de movimiento, asignacion de movimiento y
    // destructor por defecto
    BotonConTexto(BotonConTexto &&otro) noexcept;
    BotonConTexto &operator=(BotonConTexto &&) noexcept;
    ~BotonConTexto();

    void establecer_contenedor(const sf::FloatRect &);

    /* Establece la posicion relativa */
    void establecer_posicion(
        const sf::Vector2f &posicion, //
        Align align = Align::Left     //
    );
    bool colisiona(const sf::Vector2i &mousePos) const;
    void activar();
    void desactivar();
    void activacion_condicional(bool condicion);
    size_t get_id() const;
    bool esta_activo() const;
    sf::FloatRect get_rect() const;
    void actualizar();
    virtual void set_font(const OptionalFont &new_font) override;
    virtual void draw(
        sf::RenderTarget &target, //
        sf::RenderStates states   //
    ) const override;
};
