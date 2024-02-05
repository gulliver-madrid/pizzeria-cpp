#pragma once

#include "enlace_vista/enlace_vista.h"
#include "globales.h"
#include "modelo_amplio/modelo_amplio.h"
#include "shared/font.h"
#include "shared/num_nivel.h"
#include "tiempo.h"
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

class MotorNivel {
  private:
    std::optional<ModeloAmplio> modelo_amplio;
    std::shared_ptr<ControladorClicks> controlador_clicks;
    std::shared_ptr<EjecucionEnProceso> ejecucion_en_proceso;
    std::shared_ptr<GestorTimer> timer_antes_resultado;
    const std::shared_ptr<DatosNivel> datos_nivel;
    const std::shared_ptr<Grid> grid;
    sf::Sound sound;

    std::optional<Comando> _procesa_click(
        const std::shared_ptr<const BotonesApp>, //
        const FaseNivel fase_actual              //
    );
    std::shared_ptr<EnlaceVista> MotorNivel::_crear_enlace_vista( //
        const modelo::ControlPizzas &
    );
    std::optional<AccionGeneral> _procesar_evento(
        sf::Event,                              //
        const std::shared_ptr<const BotonesApp> //
    );
    std::optional<AccionGeneral> _procesa_cambio_de_fase(FaseNivel nueva_fase);

  public:
    const std::shared_ptr<Globales> globales;
    const NumNivelOpcional &num_nivel;
    std::shared_ptr<EnlaceVista> enlace_vista;

    MotorNivel(
        std::shared_ptr<Globales> globales = nullptr,          //
        std::shared_ptr<DatosNivel> datos_nivel = nullptr,     //
        const NumNivelOpcional num_nivel = NumNivelOpcional(), //
        std::shared_ptr<Grid> grid = nullptr                   //
    );
    void setup();
    std::optional<AccionGeneral> aplica_comando(const Comando &);
    std::optional<AccionGeneral> procesar_evento(sf::Event);
    std::optional<AccionGeneral> procesar_ciclo();
    void actualizar_interfaz_grafico();
    void establecer_fase(FaseNivel);
    std::shared_ptr<VistaObservable> get_vista() const;
    void tick(sf::Time transcurrido);
};
