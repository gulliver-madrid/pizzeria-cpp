#include "datos_niveles.h"
#include "setup_juego.h"
#include "textos.h"

using modelo::Pedidos;
using dominio::TipoPizza;

const auto dinamicos =
    Pedidos{ //
            {//
             Pedido(
                 {{TipoPizza::Margarita, PedidoTipoPizza{2}},
                  {TipoPizza::Pepperoni, PedidoTipoPizza{1}}}
             ),
             Pedido(
                 {{TipoPizza::Margarita, PedidoTipoPizza{1}},
                  {TipoPizza::CuatroQuesos, PedidoTipoPizza{1}}}
             )
            }
    };

const DatosNivel datos_niveles[] = {
    // TODO: adaptar texto instrucciones al nivel correspondiente
    DatosNivel{
        INSTRUCCIONES_NIVEL_ESTATICO, //
        Pedidos{{
            Pedido(
                {{TipoPizza::Margarita, PedidoTipoPizza{3}},
                 {TipoPizza::CuatroQuesos, PedidoTipoPizza{2}}}
            ),
        }},
        true
    },
    DatosNivel{
        INSTRUCCIONES_NIVEL_DINAMICO, //
        dinamicos
    },
    DatosNivel{
        INSTRUCCIONES_NIVEL_DINAMICO, //
        Pedidos{                      //
                {                     //
                 Pedido({{TipoPizza::Margarita, PedidoTipoPizza{2}}}),
                 Pedido(
                     {{TipoPizza::Margarita, PedidoTipoPizza{2}},
                      {TipoPizza::Pepperoni, PedidoTipoPizza{1}}}
                 ),
                 Pedido(
                     {{TipoPizza::Margarita, PedidoTipoPizza{1}},
                      {TipoPizza::CuatroQuesos, PedidoTipoPizza{1}},
                      {TipoPizza::Pepperoni, PedidoTipoPizza{1}}}
                 )
                }
        }
    },
    {INSTRUCCIONES_NIVEL_ESTATICO, //
     Pedidos{{
         Pedido({
             {TipoPizza::Margarita, PedidoTipoPizza{6}},
             {TipoPizza::Pepperoni, PedidoTipoPizza{4}},
             {TipoPizza::CuatroQuesos, PedidoTipoPizza{3}},
         }),
     }},
     true}

};
const int NUM_DATOS_NIVELES = sizeof(datos_niveles) / sizeof(datos_niveles[0]);
