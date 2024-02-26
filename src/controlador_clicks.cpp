#include "controlador_clicks.h"
#include "fase_nivel.h"
#include "globales.h"
#include "modelo_amplio/comandos.h"
#include "modelo_amplio/modelo_amplio.h"
#include "vista/basicos_vista.h"
#include "vista/botones/botones_app.h"
#include "vista/paneles_observables.h"

// TODO: filtrar por paneles
std::optional<Comando> ControladorClicks::genera_comando(
    const FuncionPulsado &pulsado,                          //
    const std::shared_ptr<const BotonesApp> &botones,       //
    const FaseNivel fase_actual,                            //
    const sf::Vector2i &mouse_pos,                          //
    const std::shared_ptr<const PanelesObservables> paneles //
) {
    // Fijos
    if (pulsado(botones->generales.salir)) {
        return Comando::Salir{};
    } else if (pulsado(botones->generales.reiniciar)) {
        return Comando::Reiniciar{};
    } else if (pulsado(botones->generales.alternar_grid)) {
        return Comando::AlternarGrid{};
    }

    // Dependientes de la fase
    if (pulsado(botones->empezar)) {
        assert(fase_actual == FaseNivel::MostrandoInstrucciones);
        return Comando::Empezar{};
    }

    // TODO: comprobar solo si los paneles estan visibles
    if (paneles->colisiona(IndicePanel::PANEL_ENCARGAR, mouse_pos)) {
        for (const auto &[tp, boton] : botones->encargar) {
            if (pulsado(boton)) {
                assert(fase_actual == FaseNivel::Activa);
                return Comando::Encargar{tp};
            }
        }
    }
    if (paneles->colisiona(IndicePanel::PANEL_PREPARADAS, mouse_pos)) {
        for (const auto &[tp, boton] : botones->despachar) {
            if (pulsado(boton)) {
                assert(fase_actual == FaseNivel::Activa);
                return Comando::Despachar{tp};
            }
        }
    }

    return std::nullopt;
}

std::optional<Comando> ControladorClicks::procesa_click(
    const std::shared_ptr<Globales> globales,               //
    const std::shared_ptr<const BotonesApp> &botones,       //
    const FaseNivel fase_actual,                            //
    const sf::Vector2i &mouse_pos,                          //
    const std::shared_ptr<const PanelesObservables> paneles //
) {
    const auto pulsado =
        [globales, &mouse_pos](const std::shared_ptr<BotonConTexto> boton) {
            auto deteccion = globales->detecta_colision(boton, mouse_pos);
            return deteccion;
        };
    std::optional<Comando> comando = genera_comando( //
        pulsado, botones, fase_actual, mouse_pos, paneles
    );
    return comando;
}
