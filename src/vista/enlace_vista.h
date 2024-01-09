#pragma once

#include <SFML/System/Time.hpp>
#include <memory>

struct ActivacionBotones;
struct Estado;
struct EstadoModelo;
struct Vista;

namespace sf {
    class RenderTarget;
} // namespace sf

namespace impl {
    ActivacionBotones obtener_activacion_botones( //
        const EstadoModelo &estado_modelo
    );
}

/* Debe ser un intermediario entre el modelo y la vista */
class EnlaceVista {
    // TODO: hacer vista privado
    // TODO: implementar los metodos que faltan

  public:
    std::shared_ptr<Vista> vista;
    EnlaceVista(std::shared_ptr<Vista> vista) : vista(vista) {}
    void on_cambio_a_fase_activa() const;
    void on_cambio_a_fase_espera_antes_de_resultado() const;
    void esconder_paneles() const;
    void actualizarIU(
        sf::RenderTarget &(target),        //
        const Estado &estado,              //
        const sf::Time &tiempo_real_actual //
    );
};
