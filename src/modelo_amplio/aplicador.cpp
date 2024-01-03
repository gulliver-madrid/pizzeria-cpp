#include "aplicador.h"
#include "../estado_nivel.h"
#include "comandos.h"
#include "realizador_base.h"
#include <variant>

#define SWITCH(variante)                                                       \
    using T = std::decay_t<decltype(comando_data)>;                            \
    if (false) { /* Para inicializar los bloques if else */                    \
    }
#define CASE(comando, accion)                                                  \
    else if constexpr (std::is_same_v<T, Comando::comando>) {                  \
        return accion;                                                         \
    }

/*
Aplica un comando y devuelve la nueva
fase, si correspondiera cambiar
*/
std::optional<FaseNivel> aplicador::aplicar_comando( //
    RealizadorBase &realizador,                      //
    const Comando &comando                           //

) {
    return std::visit(
        [&realizador](auto &&comando_data) -> std::optional<FaseNivel> {
            SWITCH(comando_data)
            CASE(Empezar, realizador.empezar())
            CASE(Salir, FaseNivel::Saliendo)
            CASE(Reiniciar, FaseNivel::Reiniciando)
            CASE(AlternarGrid, realizador.alternar_grid())
            CASE(Encargar, realizador.encargar_pizza(comando_data.tp))
            CASE(Despachar, realizador.despachar_pizza(comando_data.tp))
            return std::nullopt;
        },
        comando.comando_data
    );
}
#undef SWITCH
#undef CASE
