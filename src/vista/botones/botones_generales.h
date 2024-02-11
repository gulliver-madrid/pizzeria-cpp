#pragma once

#include "../vista_shared.h"
#include <memory>

class BotonConTexto;

struct BotonesGenerales {
    std::shared_ptr<BotonConTexto> alternar_grid;
    std::shared_ptr<BotonConTexto> reiniciar;
    std::shared_ptr<BotonConTexto> salir;
    void alinear();
    Botones obtener_todos() const;
};

BotonesGenerales crear_botones_generales();
