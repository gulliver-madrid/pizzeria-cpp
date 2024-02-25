#pragma once

#include "../vista/vista_shared.h"

class ModeloInterno;

class PresentadorPaneles {
  public:
    const ModeloInterno &modelo;

    PresentacionPreparacionPizzas obtener_vista_preparacion();
    PizzasToStrings obtener_vista_preparadas();
    VistaPedidos obtener_presentacion_pedidos();
};
