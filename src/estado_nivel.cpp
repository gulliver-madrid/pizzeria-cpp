#include "estado_nivel.h"
#include "general.h"

Estado::Estado(FaseNivel fase, modelo::ControlPizzas &control)
    : fase_actual(fase), control_pizzas(control) {
    assert(encargos.total() == 0);
    fase_actual = FaseNivel::MostrandoInstrucciones;
    establecido = true;
}
