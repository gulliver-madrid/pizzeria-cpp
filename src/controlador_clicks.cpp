#include "controlador_clicks.h"
#include "comandos.h"
#include "estado_nivel.h"
#include "globales.h"
#include "realizador_base.h"
#include "vista/botones_app.h"

std::optional<Comando> ControladorClicks::genera_comando(
    const std::function<bool(const BotonConTexto &boton)> &pulsado, //
    const BotonesApp &botones,                                      //
    const FaseNivel fase_actual                                     //
) {
    // Fijos
    if (pulsado(botones.generales.salir)) {
        return Comando::Salir{};
    } else if (pulsado(botones.generales.reiniciar)) {
        return Comando::Reiniciar{};
    } else if (pulsado(botones.generales.alternar_grid)) {
        return Comando::AlternarGrid{};
    }
    // Dependientes de la fase
    switch (fase_actual) {
        case FaseNivel::MostrandoInstrucciones:
            if (pulsado(botones.empezar)) {
                return Comando::Empezar{};
            }
            break;
        case FaseNivel::Activa:
            for (const auto &[tp, boton] : botones.encargar) {
                if (pulsado(boton)) {
                    return Comando::Encargar{tp};
                }
            }
            for (const auto &[tp, boton] : botones.despachar) {
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

#define SWITCH(variante)                                                       \
    using T = std::decay_t<decltype(variante)>;                                \
    if (false) { /* Para inicializar los bloques if else */                    \
    }
#define CASE(comando, accion)                                                  \
    else if constexpr (std::is_same_v<T, Comando::comando>) {                  \
        return accion;                                                         \
    }
/* Aplica un comando y devuelve la nueva fase, si correspondiera cambiar */
std::optional<FaseNivel> ControladorClicks::aplica_comando( //
    RealizadorBase &realizador,                             //
    const Comando &comando                                  //

) {
    return std::visit(
        [&realizador](auto &&variante) -> std::optional<FaseNivel> {
            SWITCH(variante)
            CASE(Empezar, realizador.empezar())
            CASE(Salir, FaseNivel::Saliendo)
            CASE(Reiniciar, FaseNivel::Reiniciando)
            CASE(AlternarGrid, realizador.alternar_grid())
            CASE(Encargar, realizador.encargar_pizza(variante.tp))
            CASE(Despachar, realizador.despachar_pizza(variante.tp))
            return std::nullopt;
        },
        comando.variante
    );
}
#undef SWITCH
#undef CASE

std::optional<FaseNivel> ControladorClicks::procesa_click(
    Globales &globales,           //
    const BotonesApp &botones,    //
    const Estado &estado,         //
    RealizadorBase &realizador,   //
    const sf::Vector2i &mouse_pos //

) {
    const auto pulsado = [&globales, &mouse_pos](const BotonConTexto &boton) {
        return globales.detecta_colision(boton, mouse_pos);
    };
    std::optional<Comando> comando = genera_comando( //
        pulsado, botones, estado.fase_actual
    );
    if (!comando) {
        return std::nullopt;
    }
    return aplica_comando(realizador, comando.value());
}
