#include "modelo_amplio.h"
#include "../fase_nivel.h"
#include "comandos.h"

ModeloAmplio::ModeloAmplio(const DatosModeloInterno &datos_modelo_interno)
    : fase_actual(FaseNivel::MostrandoInstrucciones),
      modelo_interno(datos_modelo_interno) {
    establecido = true;
}

FaseNivel ModeloAmplio::get_fase_actual() { //
    return fase_actual;
}
