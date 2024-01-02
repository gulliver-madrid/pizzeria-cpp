#include "modelo_amplio.h"
#include "comandos.h"
#include "general.h"
#include "realizador.h"

ModeloAmplio::ModeloAmplio(const DatosNivel &datos_nivel)
    : estado(FaseNivel::MostrandoInstrucciones, datos_nivel) {}

FaseNivel ModeloAmplio::get_fase_actual() { //
    return estado.fase_actual;
}

std::optional<FaseNivel> ModeloAmplio::aplica_comando( //
    const Comando &comando                             //
) {
    Realizador realizador = {estado};
    auto result = aplicador::aplicar_comando(realizador, comando);
    return result;
}
