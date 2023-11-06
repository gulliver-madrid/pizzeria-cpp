#include "estado_nivel.h"
#include "general.h"

EstadoModelo::EstadoModelo(modelo::ControlPizzas &control)
    : control_pizzas(control) {
    assert(encargos.total() == 0);
}

Estado::Estado(FaseNivel fase, modelo::ControlPizzas &control)
    : fase_actual(fase), estado_modelo(control) {
    fase_actual = FaseNivel::MostrandoInstrucciones;
    establecido = true;
}
