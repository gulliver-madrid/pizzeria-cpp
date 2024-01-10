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
  private:
    void on_cambio_a_fase_activa() const;
    void on_cambio_a_fase_espera_antes_de_resultado() const;

  public:
    std::shared_ptr<Vista> vista;

    EnlaceVista(std::shared_ptr<Vista> vista) : vista(vista) {}
    void on_cambio_de_fase(FaseNivel &);
    void esconder_paneles() const;
    void actualizarIU(
        sf::RenderTarget &(target),        //
        const ModeloAmplio &,              //
        const sf::Time &tiempo_real_actual //
    );
};
