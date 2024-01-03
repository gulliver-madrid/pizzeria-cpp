#include "realizador.h"
#include "estado_nivel.h"
#include "general.h"
#include <cassert>

using NuevaFase = std::optional<FaseNivel>;

Realizador::Realizador(Estado &estado) : estado(estado) {}

/* Encarga una pizza a la cocina del tipo indicado */
NuevaFase Realizador::encargar_pizza( //
    const dominio::TipoPizza tp
) {
    assert(estado.fase_actual == FaseNivel::Activa);
    estado.estado_modelo.anadir_encargo(tp);
    return std::nullopt;
}

/*
 * Despacha una pizza a los clientes del tipo indicado. Devuelve la nueva
 * fase si corresponde.
 */
NuevaFase Realizador::despachar_pizza( //
    const dominio::TipoPizza tp
) {
    assert(estado.fase_actual == FaseNivel::Activa);
    const auto pedidos_cubiertos = estado.estado_modelo.despachar_pizza(tp);
    if (pedidos_cubiertos) {
        return FaseNivel::EsperaAntesDeResultado;
    }
    return std::nullopt;
}

NuevaFase Realizador::alternar_grid() {
    assert(MODO_DESARROLLO);
    estado.mostrando_grid = !estado.mostrando_grid;
    return std::nullopt;
}

NuevaFase Realizador::empezar() {
    assert(estado.fase_actual == FaseNivel::MostrandoInstrucciones);
    return FaseNivel::Activa;
}
