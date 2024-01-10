#pragma once

#include <SFML/System/Time.hpp>
#include <memory>

enum class FaseNivel;
struct ActivacionBotones;
struct ModeloAmplio;
struct ModeloInterno;
struct Vista;

namespace sf {
    class RenderTarget;
} // namespace sf

namespace enlace_vista_impl {
    ActivacionBotones obtener_activacion_botones( //
        const ModeloInterno &modelo_interno
    );
}

/* Debe ser un intermediario entre el modelo y la vista */
class EnlaceVista {
    // TODO: hacer vista privado
    // TODO: implementar los metodos que faltan

  public:
    std::shared_ptr<Vista> vista;

    EnlaceVista(std::shared_ptr<Vista> vista) : vista(vista) {}
    void on_cambio_de_fase(FaseNivel &);
    void esconder_paneles() const;
    void actualizarIU(
        sf::RenderTarget &,                //
        const ModeloAmplio &,              //
        const sf::Time &tiempo_real_actual //
    );
    void dibujar_vista(sf::RenderTarget &);
};
