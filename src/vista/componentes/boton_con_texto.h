#pragma once

#include "../posiciones.h"
#include "boton_data.h"
#include "componente.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <memory>
#include <optional>

class Etiqueta;

namespace sf {
    class RenderTarget;
}

struct Posicionamiento;

enum class Align { //
    Left,
    Right
};

///////////////////////////////////////////
// BotonConTexto
//////////////////////////////////////////

class BotonConTexto : public ComponenteConFont {
  private:
    static size_t _proximo_id;
    std::optional<size_t> _id;

    sf::RectangleShape _forma;
    std::shared_ptr<Etiqueta> _etiqueta;

    std::unique_ptr<Posicionamiento> posicionamiento;
    // Solo puede modificarse la escala en la construccion
    float _escala = 1;
    bool _activo = true;
    std::optional<sf::Color> colorBotonActivo;

    BotonConTexto();
    void _asignar_id();
    void _actualizar_posicionamiento();
    void _resize();
    float _get_margen_ambos_lados();

  public:
    bool visible = false;
    bool usar_posicion_relativa_para_dibujo = false;
    BotonConTexto(
        const BotonData boton_data, //
        float escala = 1            //
    );
    BotonConTexto(
        const BotonData boton_data,       //
        const PosicionRelativa &posicion, //
        Align align = Align::Left,        //
        float escala = 1                  //
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
    void establecer_posicion_relativa(
        const PosicionRelativa &posicion, //
        Align align = Align::Left         //
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
    void establecer_posicion_de_dibujo(
        const sf::Vector2f posicion, const float escala
    );
    virtual void draw(sf::RenderTarget &, sf::RenderStates) const override;
};
