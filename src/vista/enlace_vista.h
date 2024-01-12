#pragma once

#include "../modelo_amplio/modelo_amplio.h"
#include "../observador_fase.h"
#include "presentacion_vista.h"
#include <memory>

struct ActivacionBotones;
struct ModeloInterno;
struct Vista;

namespace sf {
    class RenderTarget;
    class Time;
} // namespace sf

namespace enlace_vista_impl {
    ActivacionBotones obtener_activacion_botones( //
        const ModeloInterno &modelo_interno
    );
}

/* Debe ser un intermediario entre el modelo y la vista */
class EnlaceVista : public ObservadorFase {
    // TODO: hacer vista privado
    // TODO: implementar los metodos que faltan
  private:
    std::shared_ptr<PresentacionVista> presentacion_vista;

    void cambiar_visibilidad_instrucciones(bool);
    void cambiar_visibilidad_resultado(bool);

  public:
    std::shared_ptr<Vista> vista;

    EnlaceVista();
    void set_vista(std::shared_ptr<Vista> vista);
    void on_cambio_de_fase(FaseNivel);
    void esconder_paneles() const;
    void actualizar_interfaz_grafico(
        sf::RenderTarget &,                //
        const ModeloAmplio &,              //
        const sf::Time &tiempo_real_actual //
    );
    PresentacionVista get_presentacion_vista() const;
    void dibujar_vista(sf::RenderTarget &);
};
