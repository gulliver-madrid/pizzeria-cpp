#include "datos_niveles.h"
#include "setup_juego.h"
#include "textos.h"

using dominio::TipoPizza;
using modelo::Pedidos;

const DatosNivel datos_niveles[] = {
    // TODO: adaptar texto instrucciones al nivel correspondiente
    DatosNivel{
        INSTRUCCIONES_NIVEL_DINAMICO, //
        Pedidos{{
            Pedido({{TipoPizza::Margarita, 2}, {TipoPizza::Pepperoni, 1}}),
        }}
    },
    DatosNivel{
        INSTRUCCIONES_NIVEL_DINAMICO, //
        Pedidos{{
            Pedido({{TipoPizza::Margarita, 3}, {TipoPizza::CuatroQuesos, 1}}),
        }}
    },
    DatosNivel{
        INSTRUCCIONES_NIVEL_DINAMICO, //
        Pedidos{
            //
            {//
             Pedido({{TipoPizza::Margarita, 2}, {TipoPizza::Pepperoni, 1}}),
             Pedido({{TipoPizza::Margarita, 1}, {TipoPizza::CuatroQuesos, 1}})
            }
        }
    },
    DatosNivel{
        INSTRUCCIONES_NIVEL_DINAMICO, //
        Pedidos{{
            Pedido({{TipoPizza::Margarita, 2}}),
            Pedido(
                {{TipoPizza::Margarita, 1},
                 {TipoPizza::CuatroQuesos, 1},
                 {TipoPizza::Pepperoni, 1}}
            ),
            Pedido(
                {{TipoPizza::Margarita, 1},
                 {TipoPizza::CuatroQuesos, 1},
                 {TipoPizza::Funghi, 2},
                 {TipoPizza::Vegetariana, 1},
                 {TipoPizza::Pepperoni, 1}}
            ),
            Pedido(
                {{TipoPizza::Margarita, 2}, //
                 {TipoPizza::Pepperoni, 1}}
            ),
        }}
    },
    {INSTRUCCIONES_NIVEL_DINAMICO, //
     Pedidos{{
         Pedido({
             {TipoPizza::Margarita, 6},
             {TipoPizza::Pepperoni, 4},
             {TipoPizza::CuatroQuesos, 3},
         }),
     }}}
};
const int NUM_DATOS_NIVELES = sizeof(datos_niveles) / sizeof(datos_niveles[0]);
