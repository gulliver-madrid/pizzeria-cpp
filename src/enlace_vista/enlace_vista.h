#pragma once

#include "../modelo_amplio/modelo_amplio.h"
#include "../observador_fase.h"
#include "../vista/presentacion_vista.h"
#include "../vista/vista.h"
#include <memory>

struct ActivacionBotones;
class BotonesApp;
class ModeloInterno;
class Vista;

namespace sf {
    class RenderTarget;
    class Time;
} // namespace sf

namespace enlace_vista_impl {
    ActivacionBotones obtener_activacion_botones(const ModeloInterno &);
}

/* Debe ser un intermediario entre el modelo y la vista */
class EnlaceVista : public ObservadorFase {
    // TODO: implementar los metodos que faltan
  private:
    std::shared_ptr<Vista> vista;

  public:
    EnlaceVista();
    void set_vista(std::shared_ptr<Vista>);
    void on_cambio_de_fase(FaseNivel);
    void actualizar_interfaz_grafico(const ModeloAmplio &);

    const std::shared_ptr<const BotonesApp> get_botones() const;
    std::shared_ptr<VistaObservable> get_vista() const;
    void dibujar_vista(sf::RenderTarget &);
};
