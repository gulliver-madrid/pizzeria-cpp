#pragma once

#include "control_pizzas.h"
#include "tiempo.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cassert>
#include <iostream>

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
  private:
    union {
        PedidosEstaticos estaticos;
        PedidosDinamicos dinamicos;
    };
    TipoSistemaPedidos tipo;

  public:
    PedidosNivel(PedidosEstaticos pedidos_) : estaticos(pedidos_) {
        std::cout << "en el constructor de PedidosNivel usando PedidosEstaticos"
                  << std::endl;
        tipo = TipoSistemaPedidos::Estatico;
    }
    PedidosNivel(PedidosDinamicos pedidos_) : dinamicos(pedidos_) {
        std::cout << "en el constructor de PedidosNivel usando PedidosDinamicos"
                  << std::endl;
        tipo = TipoSistemaPedidos::Dinamico;
    }
    PedidosNivel(PedidosNivel &pedidos_nivel) {
        std::cout << "en el constructor de PedidosNivel" << std::endl;
        if (pedidos_nivel.get_tipo() == TipoSistemaPedidos::Estatico) {
            std::cout << "El tipo es estatico" << std::endl;
            tipo = TipoSistemaPedidos::Estatico;
            estaticos = pedidos_nivel.estaticos;
        } else if (pedidos_nivel.get_tipo() == TipoSistemaPedidos::Dinamico) {
            std::cout << "El tipo es dinámico" << std::endl;
            tipo = TipoSistemaPedidos::Dinamico;
            dinamicos = pedidos_nivel.dinamicos;
        } else {
            std::cout << "El tipo no es estático ni dinámico" << std::endl;
            assert(false);
        }
    }
    ~PedidosNivel() {
        if (tipo == TipoSistemaPedidos::Estatico) {
            estaticos.~PedidosEstaticos();
        } else {
            dinamicos.~PedidosDinamicos();
        }
    }
    TipoSistemaPedidos get_tipo() const { return tipo; }

    const PedidosEstaticos &get_pedidos_estaticos_const() const {
        assert(tipo == TipoSistemaPedidos::Estatico);
        return estaticos;
    }
};

struct DatosNivel {
    std::string instrucciones;
    PedidosNivel sistema_pedidos;
    DatosNivel(std::string instr, PedidosNivel pedidos)
        : instrucciones(instr), sistema_pedidos(pedidos) {
        std::cout << "En el constructor de DatosNivel que usa PedidosNivel - "
                  << instr << std::endl
                  << std::endl;
    }
    DatosNivel(std::string instr, PedidosEstaticos pedidos)
        : instrucciones(instr), sistema_pedidos(pedidos) {
        std::cout
            << "En el constructor de DatosNivel que usa PedidosEstaticos - "
            << instr << std::endl
            << std::endl;
    }
};
