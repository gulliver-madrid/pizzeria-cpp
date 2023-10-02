#include "datos_niveles.h"
#include "setup_juego.h"
#include "textos.h"

const auto dinamicos =
    PedidosDinamicos{{// vector
                      {{TipoPizza::Margarita, PedidoTipoPizza{3, 0}}},
                      {{TipoPizza::Margarita, PedidoTipoPizza{3, 0}}}}};

const DatosNivel datos_niveles[] = {
    // TODO: adaptar texto instrucciones al nivel correspondiente
    DatosNivel(
        "NIVEL_1", //
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
        })
    ),
    DatosNivel{
        "NIVEL_2", //
        PedidosNivel{dinamicos}},
    {"NIVEL_3", //
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
     })}

};
const int NUM_DATOS_NIVELES = sizeof(datos_niveles) / sizeof(datos_niveles[0]);
