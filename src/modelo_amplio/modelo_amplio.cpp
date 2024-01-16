#include "modelo_amplio.h"
#include "../observador_fase.h"
#include "comandos.h"

ModeloAmplio::ModeloAmplio(
    const std::optional<DatosModeloInterno> datos_modelo_interno
)
    : modelo_interno(datos_modelo_interno) {
    establecido = true;
}

void ModeloAmplio::set_fase_actual(FaseNivel nueva) { //
    if (nueva == fase_actual)
        return;
    fase_actual = nueva;
    for (auto observador : observadores_fase) {
        observador->on_cambio_de_fase(nueva);
    }
}

FaseNivel ModeloAmplio::get_fase_actual() const { //
    return fase_actual;
}
