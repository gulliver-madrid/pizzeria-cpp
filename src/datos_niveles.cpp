#include "datos_niveles.h"
#include "setup_juego.h"
#include "textos.h"

DatosNivel datos[2] = {
    {INSTRUCCIONES_NIVEL_1, //
     construir_pedidos({
         {

             DatosNivelTipoPizza{Margarita, 2, 8},
         },
         {

             DatosNivelTipoPizza{Pepperoni, 0, 4},
         },
         {

             DatosNivelTipoPizza{CuatroQuesos, 0, 3},
         },
     })},
    {INSTRUCCIONES_NIVEL_2, //
     construir_pedidos({
         {
             DatosNivelTipoPizza{Margarita, 2, 6},
         },
         {
             DatosNivelTipoPizza{Pepperoni, 1, 3},
         },
         {
             DatosNivelTipoPizza{CuatroQuesos, 0, 6},
         },
     })},
};
