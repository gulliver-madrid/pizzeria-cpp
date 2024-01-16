#pragma once

#include "globales.h"
#include "modelo_amplio/modelo_amplio.h"
#include "shared.h"
#include "tiempo.h"
#include "vista/enlace_vista.h"
#include "vista/grid.h"
#include "vista/vista.h"

enum class FaseNivel;
class BotonesApp;
struct ControladorClicks;
struct DatosNivel;
struct EjecucionEnProceso;
struct Globales;

namespace modelo {
    struct ControlPizzas;
}

enum class AccionGeneral { SiguienteNivel, Reiniciar, Salir };

// CambioFase(previa, nueva)
using CambioFase = std::pair<FaseNivel, FaseNivel>;

struct Nivel {
  private:
    std::optional<ModeloAmplio> modelo_amplio;
    OptionalFont font;

    std::optional<FaseNivel> _procesa_click(
        const std::shared_ptr<const BotonesApp>, //
        const FaseNivel fase_actual              //
    );
    std::shared_ptr<EnlaceVista> Nivel::_crear_enlace_vista( //
        const modelo::ControlPizzas &control_pizzas
    );
    std::optional<FaseNivel> _procesarEvento(
        sf::Event,                              //
        const std::shared_ptr<const BotonesApp> //
    );
    std::optional<AccionGeneral> Nivel::_procesa_cambio_de_fase(
        EjecucionEnProceso &ejecucion_en_proceso, FaseNivel nueva_fase
    );

  public:
    const std::shared_ptr<Globales> globales;
    const std::shared_ptr<DatosNivel> datos_nivel;
    const NumNivelOpcional &num_nivel;
    const std::shared_ptr<Grid> grid;

    const bool es_el_ultimo;
    std::shared_ptr<ControladorClicks> controlador_clicks;
    std::shared_ptr<EnlaceVista> enlace_vista;

    Nivel(
        std::shared_ptr<Globales> globales = nullptr,          //
        std::shared_ptr<DatosNivel> datos_nivel = nullptr,     //
        const NumNivelOpcional num_nivel = NumNivelOpcional(), //
        std::shared_ptr<Grid> grid = nullptr,                  //
        bool es_el_ultimo = false                              //
    );
    AccionGeneral ejecutar();
    void establecer_fase(FaseNivel);
    std::shared_ptr<VistaObservable> get_vista() const;
};
