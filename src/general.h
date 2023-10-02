#pragma once

#include "control_pizzas.h"
#include "tiempo.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cassert>
#include <iostream>
#include <variant>

#define MAXIMO_PIZZAS_EN_PREPARACION 3
#define MAXIMO_PIZZAS_PREPARADAS 4

namespace tiempos {
    const auto RETARDO_ANTES_DE_RESULTADO = Tiempo::desde_segundos(2.5);
    const auto ESPERA_ENTRE_NIVELES = Tiempo::desde_segundos(2);
} // namespace tiempos

enum class FaseNivel {
    MostrandoInstrucciones,
    Activa,
    EsperaAntesDeResultado,
    MostrandoResultado,
    Reiniciando,
    Saliendo
};

/* Datos para un nivel determinado de un tipo concreto de pizza */
struct DatosNivelTipoPizza {
    TipoPizza tipo;
    int pizzas_preparadas_iniciales = 0;
    int objetivo_pizzas = 0;
};

/* Una cantidad determinada de pizzas de cada tipo */
struct PedidosEstaticos {
    std::map<TipoPizza, DatosNivelTipoPizza> pizzas;
};

/* Una lista de pedidos */
struct PedidosDinamicos {
    std::vector<Pedido> listado;
};

/* Guarda la información relativa al nivel */
struct PedidosNivel {
    std::variant<PedidosEstaticos, PedidosDinamicos> pedidos;

    TipoSistemaPedidos tipo = TipoSistemaPedidos::Ninguno;

    PedidosNivel() { //
        tipo = TipoSistemaPedidos::Ninguno;
    }
    PedidosNivel(PedidosEstaticos pedidos_) : pedidos(pedidos_) {
        assert(tipo == TipoSistemaPedidos::Ninguno);
        tipo = TipoSistemaPedidos::Estatico;
    }
    PedidosNivel(PedidosDinamicos pedidos_) : pedidos(pedidos_) {
        assert(tipo == TipoSistemaPedidos::Ninguno);
        tipo = TipoSistemaPedidos::Dinamico;
    }
};

struct DatosNivel {
    std::string instrucciones;
    PedidosNivel sistema_pedidos;
    DatosNivel(std::string instr, PedidosNivel pedidos) : instrucciones(instr) {
        if (std::holds_alternative<PedidosEstaticos>(pedidos.pedidos)) {
            sistema_pedidos.pedidos =
                std::get<PedidosEstaticos>(pedidos.pedidos);
            sistema_pedidos.tipo = TipoSistemaPedidos::Estatico;
        } else if (std::holds_alternative<PedidosDinamicos>(pedidos.pedidos)) {
            sistema_pedidos.pedidos =
                std::get<PedidosDinamicos>(pedidos.pedidos);
            sistema_pedidos.tipo = TipoSistemaPedidos::Dinamico;
        } else {
            assert(false);
        }
    }
};
