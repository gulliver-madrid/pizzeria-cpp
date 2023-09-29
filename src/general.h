#pragma once

#include "modelo/modelo.h"
#include <SFML/Audio.hpp>
#include <cassert>

#define MAXIMO_PIZZAS_EN_PREPARACION 3
#define MAXIMO_PIZZAS_PREPARADAS 4

namespace tiempos {
    const auto RETARDO_ANTES_DE_RESULTADO = Tiempo::desde_segundos(2.5);
    const auto ESPERA_ENTRE_NIVELES = Tiempo::desde_segundos(2);
} // namespace tiempos

struct Globales {
    sf::RenderWindow window;
    sf::Font font;
    std::optional<sf::SoundBuffer> success_buffer;
    std::optional<sf::SoundBuffer> button_click_buffer;
    sf::Music music;
};

enum class FaseNivel {
    MostrandoInstrucciones,
    Activa,
    EsperaAntesDeResultado,
    MostrandoResultado,
    Reiniciando,
    Saliendo
};

struct ControlPizzasDinamico {
    // TODO: implementar el control de pedidos cubiertos parcial o totalmente
};

enum class TipoSistemaPedidos { Estatico, Dinamico };

struct ControlPizzas {
  private:
    union {
        PizzasAContadores contadores;
        ControlPizzasDinamico control_dinamico;
    };

  public:
    TipoSistemaPedidos tipo;
    ControlPizzas(PizzasAContadores contadores_) : contadores(contadores_) {
        tipo = TipoSistemaPedidos::Estatico;
    }
    ~ControlPizzas() {
        if (tipo == TipoSistemaPedidos::Estatico) {
            contadores.~PizzasAContadores(
            ); // Llamar al destructor explícitamente
        } else {
            control_dinamico.~ControlPizzasDinamico();
        }
    }
    const PizzasAContadores &get_contadores_const() const {
        assert(tipo == TipoSistemaPedidos::Estatico);
        return contadores;
    }
    PizzasAContadores &get_contadores() {
        assert(tipo == TipoSistemaPedidos::Estatico);
        return contadores;
    }
};

struct Estado {
    FaseNivel fase_actual = FaseNivel::MostrandoInstrucciones;
    std::optional<ControlPizzas> control_pizzas;
    Encargos encargos;
};

// Datos para un nivel determinado de un tipo concreto de pizza
struct DatosNivelTipoPizza {
    TipoPizza tipo;
    int pizzas_preparadas_iniciales = 0;
    int objetivo_pizzas = 0;
};

struct PedidosEstaticos {
    std::map<TipoPizza, DatosNivelTipoPizza> pizzas;
};

struct PedidosDinamicos {
    std::vector<Pedido> listado;
};

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
            pedidos.~PedidosEstaticos(); // Llamar al destructor explícitamente
        } else {
            pedidos_dinamicos.~PedidosDinamicos();
        }
    }

    const PedidosEstaticos &get_pedidos_estaticos_const() const {
        assert(tipo == TipoSistemaPedidos::Estatico);
        return pedidos;
    }
};

struct DatosNivel {
    std::string instrucciones;
    SistemaPedidos sistema_pedidos;
    DatosNivel(std::string instr, PedidosEstaticos pizzas)
        : instrucciones(instr), sistema_pedidos(pizzas) {}
};
