#pragma once

#include "control_pizzas.h"
#include "tiempo.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cassert>

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
struct SistemaPedidos {
  private:
    union {
        PedidosEstaticos pedidos;
        PedidosDinamicos pedidos_dinamicos;
    };
    TipoSistemaPedidos tipo;

  public:
    SistemaPedidos(PedidosEstaticos pedidos_) : pedidos(pedidos_) {
        tipo = TipoSistemaPedidos::Estatico;
    }
    ~SistemaPedidos() {
        if (tipo == TipoSistemaPedidos::Estatico) {
            pedidos.~PedidosEstaticos();
        } else {
            pedidos_dinamicos.~PedidosDinamicos();
        }
    }
    TipoSistemaPedidos get_tipo() const { return tipo; }

    const PedidosEstaticos &get_pedidos_estaticos_const() const {
        assert(tipo == TipoSistemaPedidos::Estatico);
        return pedidos;
    }
};

struct DatosNivel {
    std::string instrucciones;
    SistemaPedidos sistema_pedidos;
    // TODO: implementar constructor para pedidos dinamicos tambien
    DatosNivel(std::string instr, PedidosEstaticos pizzas)
        : instrucciones(instr), sistema_pedidos(pizzas) {}
};
