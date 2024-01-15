#include "controlador_clicks.h"
#include "fase_nivel.h"
#include "globales.h"
#include "modelo_amplio/modelo_amplio.h"
#include "vista/botones_app.h"

std::optional<Comando> ControladorClicks::genera_comando(
    const std::function<bool(const BotonConTexto &boton)> &pulsado, //
    const std::shared_ptr<const BotonesApp> &botones,               //
    const FaseNivel fase_actual                                     //
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
    switch (fase_actual) {
        case FaseNivel::MostrandoInstrucciones:
            if (pulsado(botones->empezar)) {
                return Comando::Empezar{};
            }
            break;
        case FaseNivel::Activa:
            for (const auto &[tp, boton] : botones->encargar) {
                if (pulsado(boton)) {
                    return Comando::Encargar{tp};
                }
            }
            for (const auto &[tp, boton] : botones->despachar) {
                if (pulsado(boton)) {
                    return Comando::Despachar{tp};
                }
            }
            break;
        default:
            break;
    }
    return std::nullopt;
}

std::optional<Comando> ControladorClicks::procesa_click(
    const std::shared_ptr<Globales> globales,         //
    const std::shared_ptr<const BotonesApp> &botones, //
    const FaseNivel fase_actual,                      //
    const sf::Vector2i &mouse_pos                     //
) {
    const auto pulsado = [globales, &mouse_pos](const BotonConTexto &boton) {
        return globales->detecta_colision(boton, mouse_pos);
    };
    std::optional<Comando> comando = genera_comando( //
        pulsado, botones, fase_actual
    );
    return comando;
}
