#include "realizador.h"
#include "../fase_nivel.h"
#include "../shared/dev.h"
#include "../shared/log_init.h"
#include "modelo_amplio.h"
#include <cassert>

using NuevaFase = std::optional<FaseNivel>;

Realizador::Realizador(ModeloAmplio &modelo_amplio)
    : modelo_amplio(modelo_amplio) {}

/* Encarga una pizza a la cocina del tipo indicado */
NuevaFase Realizador::encargar_pizza( //
    const dominio::TipoPizza tp
) {
    assert(modelo_amplio.get_fase_actual() == FaseNivel::Activa);
    LOG(info) << "Antes de anadir encargo" << std::endl;
    modelo_amplio.modelo_interno.anadir_encargo(tp);
    LOG(info) << "Despues de anadir encargo" << std::endl;
    return std::nullopt;
}

/*
 * Despacha una pizza a los clientes del tipo indicado. Devuelve la nueva
 * fase si corresponde.
 */
NuevaFase Realizador::despachar_pizza( //
    const dominio::TipoPizza tp
) {
    assert(modelo_amplio.get_fase_actual() == FaseNivel::Activa);
    const auto pedidos_cubiertos =
        modelo_amplio.modelo_interno.despachar_pizza(tp);
    if (pedidos_cubiertos) {
        return FaseNivel::EsperaAntesDeResultado;
    }
    return std::nullopt;
}

NuevaFase Realizador::alternar_grid() {
    assert(MODO_DESARROLLO);
    modelo_amplio.mostrando_grid = !modelo_amplio.mostrando_grid;
    return std::nullopt;
}

NuevaFase Realizador::empezar() {
    assert(
        modelo_amplio.get_fase_actual() == FaseNivel::MostrandoInstrucciones
    );
    return FaseNivel::Activa;
}
