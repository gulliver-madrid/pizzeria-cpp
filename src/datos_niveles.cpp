#include "datos_niveles.h"
#include "setup_juego.h"
#include "textos.h"

const DatosNivel datos_niveles[] = {
    {INSTRUCCIONES_NIVEL_1, //
     construir_pedidos({
         {

             DatosNivelTipoPizza{TipoPizza::Margarita, 2, 3},
         },
         {

             DatosNivelTipoPizza{TipoPizza::Pepperoni, 0, 2},
         },
         {

             DatosNivelTipoPizza{TipoPizza::CuatroQuesos, 0, 1},
         },
     })},
    {INSTRUCCIONES_NIVEL_2, //
     construir_pedidos({
         {
             DatosNivelTipoPizza{TipoPizza::Margarita, 2, 6},
         },
         {
             DatosNivelTipoPizza{TipoPizza::Pepperoni, 1, 3},
         },
         {
             DatosNivelTipoPizza{TipoPizza::CuatroQuesos, 0, 6},
         },
     })},
};
const int NUM_DATOS_NIVELES = sizeof(datos_niveles) / sizeof(datos_niveles[0]);
