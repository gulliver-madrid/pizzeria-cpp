#pragma once

#include "globales.h"
#include "shared.h"
#include "tiempo.h"
#include "vista/grid.h"
#include <memory>

struct BotonesApp;
struct EnlaceVista;
struct Estado;
struct Globales;
struct ControladorClicks;
struct DatosNivel;
namespace modelo {
    struct ControlPizzas;
}
enum class FaseNivel;

enum class AccionGeneral { SiguienteNivel, Reiniciar, Salir };

struct Nivel {
  private:
    std::optional<FaseNivel> procesarEvento(
        sf::Event,          //
        const BotonesApp &, //
        Estado &            //
    );
    std::optional<AccionGeneral> procesa_cambio_de_fase(
        FaseNivel nueva_fase,                   //
        const EnlaceVista &enlace_vista,        //
        Timer &timer_espera_antes_de_resultado, //
        FaseNivel fase_previa,                  //
        GestorTiempoJuego &gestor_tiempo        //
    );
    EnlaceVista crear_enlace_vista(
        const modelo::ControlPizzas &control_pizzas, //
        std::optional<int> objetivo_estatico         //
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
