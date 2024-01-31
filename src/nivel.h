#pragma once

#include "globales.h"
#include "modelo_amplio/modelo_amplio.h"
#include "shared/font.h"
#include "shared/num_nivel.h"
#include "tiempo.h"
#include "vista/enlace_vista.h"
#include "vista/grid.h"
#include "vista/vista.h"

class BotonesApp;
class ControladorClicks;
class Globales;
enum class FaseNivel;
struct DatosNivel;
struct EjecucionEnProceso;

namespace modelo {
    struct ControlPizzas;
}

enum class AccionGeneral { SiguienteNivel, Reiniciar, Salir };

// CambioFase(previa, nueva)
using CambioFase = std::pair<FaseNivel, FaseNivel>;

struct Nivel {
  private:
    std::shared_ptr<EjecucionEnProceso> ejecucion_en_proceso;
    std::shared_ptr<GestorTimer> timer_espera_antes_de_resultado;
    sf::Sound sound;

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

  public:
    GestorTiempoGeneral gestor_tiempo_general;
    std::optional<ModeloAmplio> modelo_amplio;
    const std::shared_ptr<Globales> globales;
    const std::shared_ptr<DatosNivel> datos_nivel;
    const NumNivelOpcional &num_nivel;
    const std::shared_ptr<Grid> grid;
    std::shared_ptr<ControladorClicks> controlador_clicks;
    std::shared_ptr<EnlaceVista> enlace_vista;

    Nivel(
        std::shared_ptr<Globales> globales = nullptr,          //
        std::shared_ptr<DatosNivel> datos_nivel = nullptr,     //
        const NumNivelOpcional num_nivel = NumNivelOpcional(), //
        std::shared_ptr<Grid> grid = nullptr                   //
    );
    void setup();
    AccionGeneral ejecutar();
    std::optional<AccionGeneral> Nivel::procesar_evento(sf::Event);
    std::optional<AccionGeneral> procesar_ciclo();
    void actualizar_interfaz_grafico(const sf::Time tiempo_real_actual);
    std::optional<AccionGeneral> procesa_cambio_de_fase(FaseNivel nueva_fase);
    void establecer_fase(FaseNivel);
    std::shared_ptr<VistaObservable> get_vista() const;
};
