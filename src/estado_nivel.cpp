#include "estado_nivel.h"
#include "datos_nivel.h"
#include "general.h"

//////// Estado

Estado::Estado(FaseNivel fase, const DatosNivel &datos_nivel)
    : fase_actual(fase), modelo_interno(datos_nivel.datos_modelo_interno) {
    establecido = true;
}
