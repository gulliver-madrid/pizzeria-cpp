#pragma once

#include "../vista_shared.h"

/**
 * Crea y posiciona los botones asociados con la accion "encargar".
 * @param font: Fuente a utilizar para el texto del boton.
 * @param tp_disponibles: Tipos de pizza disponibles para encargar.
 * @return TipoPizzaToBoton: Un mapa que asocia cada TipoPizza con un
 * BotonConTexto.
 */
TipoPizzaToBoton crear_botones_encargar(        //
    const dominio::TiposDePizza &tp_disponibles //
);
