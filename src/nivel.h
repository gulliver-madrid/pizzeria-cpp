#pragma once

#include "globales.h"
#include "modelo_amplio/modelo_amplio.h"
#include "shared.h"
#include "tiempo.h"
#include "vista/enlace_vista.h"
#include "vista/grid.h"

enum class FaseNivel;
class BotonesApp;
struct Globales;
struct ControladorClicks;
struct DatosNivel;
namespace modelo {
    struct ControlPizzas;
}

enum class AccionGeneral { SiguienteNivel, Reiniciar, Salir };

struct Nivel {
  private:
    std::optional<ModeloAmplio> modelo_amplio_opcional;

    std::optional<FaseNivel> _procesa_click(
        const std::shared_ptr<const BotonesApp> &, //
        const FaseNivel fase_actual                //
    );
    EnlaceVista _crear_enlace_vista( //
        const modelo::ControlPizzas &
    );
    std::optional<FaseNivel> _procesarEvento(
        sf::Event,                                 //
        const std::shared_ptr<const BotonesApp> &, //
        ModeloAmplio &                             //
    );
    std::optional<AccionGeneral> _procesa_cambio_de_fase(
        FaseNivel nueva_fase,                   //
        EnlaceVista &,                          //
        Timer &timer_espera_antes_de_resultado, //
        FaseNivel fase_previa,                  //
        GestorTiempoJuego &                     //
    );

  public:
    Globales &globales;
    const DatosNivel &datos_nivel;
    const NumNivel &num_nivel;
    Grid &grid;
    const bool es_el_ultimo;
    std::shared_ptr<ControladorClicks> controlador_clicks;

    Nivel(
        Globales &,         //
        const DatosNivel &, //
        const NumNivel &,   //
        Grid &,             //
        bool es_el_ultimo   //
    );
    AccionGeneral ejecutar();
};
