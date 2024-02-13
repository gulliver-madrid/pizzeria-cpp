#include "datos_niveles.h"
#include "setup_juego.h"
#include "textos.h"
#include <iostream>

using dominio::TipoPizza;
using modelo::Pedidos;

Pedido crear_pedido(std::map<TipoPizza, int> data) {
    std::map<TipoPizza, LineaPedido> contenido;
    for (const auto &par : data) {
        try {
            // Intenta convertir y asignar el valor
            const UInt value = UInt(par.second);
            contenido[par.first] = LineaPedido(value.to_int());
        } catch (const std::exception &e) {
            std::cerr << "Error en la conversión: " << e.what()
                      << " para la pizza " << static_cast<int>(par.first)
                      << '\n';
        }
    }
    return Pedido(contenido);
}

const DatosNivel datos_niveles[] = {
    // TODO: adaptar texto instrucciones al nivel correspondiente
    DatosNivel{
        INSTRUCCIONES_NIVEL_DINAMICO, //
        Pedidos{{
            crear_pedido({{TipoPizza::Margarita, 2}, {TipoPizza::Pepperoni, 1}}
            ),
        }}
    },
    DatosNivel{
        INSTRUCCIONES_NIVEL_DINAMICO, //
        Pedidos{{
            crear_pedido(
                {{TipoPizza::Margarita, 3}, {TipoPizza::CuatroQuesos, 1}}
            ),
        }}
    },
    DatosNivel{
        INSTRUCCIONES_NIVEL_DINAMICO, //
        Pedidos{
            //
            {//
             crear_pedido({{TipoPizza::Margarita, 2}, {TipoPizza::Pepperoni, 1}}
             ),
             crear_pedido(
                 {{TipoPizza::Margarita, 1}, {TipoPizza::CuatroQuesos, 1}}
             )
            }
        }
    },
    DatosNivel{
        INSTRUCCIONES_NIVEL_DINAMICO, //
        Pedidos{{
            crear_pedido({{TipoPizza::Margarita, 2}}),
            crear_pedido(
                {{TipoPizza::Margarita, 1},
                 {TipoPizza::CuatroQuesos, 1},
                 {TipoPizza::Pepperoni, 1}}
            ),
            crear_pedido(
                {{TipoPizza::Margarita, 1},
                 {TipoPizza::CuatroQuesos, 1},
                 {TipoPizza::Funghi, 2},
                 {TipoPizza::Vegetariana, 1},
                 {TipoPizza::Pepperoni, 1}}
            ),
            crear_pedido(
                {{TipoPizza::Margarita, 2}, //
                 {TipoPizza::Pepperoni, 1}}
            ),
        }}
    },
    DatosNivel{
        INSTRUCCIONES_NIVEL_DINAMICO, //
        Pedidos{{
            crear_pedido({{TipoPizza::Margarita, 2}}),
            crear_pedido(
                {{TipoPizza::Margarita, 1},
                 {TipoPizza::CuatroQuesos, 1},
                 {TipoPizza::Pepperoni, 1}}
            ),
            crear_pedido(
                {{TipoPizza::Margarita, 1},
                 {TipoPizza::CuatroQuesos, 1},
                 {TipoPizza::Funghi, 2},
                 {TipoPizza::Vegetariana, 1},
                 {TipoPizza::Pepperoni, 1}}
            ),
            crear_pedido(
                {{TipoPizza::Margarita, 2}, //
                 {TipoPizza::Barbacoa, 1}}
            ),
            crear_pedido({{TipoPizza::Margarita, 2}}),
            crear_pedido(
                {{TipoPizza::Margarita, 1},
                 {TipoPizza::CuatroQuesos, 1},
                 {TipoPizza::Primavera, 1}}
            ),
            crear_pedido(
                {{TipoPizza::Margarita, 1},
                 {TipoPizza::CuatroQuesos, 1},
                 {TipoPizza::Funghi, 2},
                 {TipoPizza::Hawaiana, 1},
                 {TipoPizza::Pepperoni, 1}}
            ),
            crear_pedido(
                {{TipoPizza::Margarita, 2}, //
                 {TipoPizza::Pepperoni, 1}}
            ),
        }}
    },
    {INSTRUCCIONES_NIVEL_DINAMICO, //
     Pedidos{{
         crear_pedido({
             {TipoPizza::Margarita, 6},
             {TipoPizza::Pepperoni, 4},
             {TipoPizza::CuatroQuesos, 3},
         }),
     }}}
};
const int NUM_DATOS_NIVELES = sizeof(datos_niveles) / sizeof(datos_niveles[0]);
