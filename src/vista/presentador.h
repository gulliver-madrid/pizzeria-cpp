#pragma once

#include <string>

namespace dominio {
    enum class TipoPizza;
}
struct Pedido;

namespace presentador {
    std::string crea_linea_completitud_pizza(
        const dominio::TipoPizza tp, int parte, int todo
    );

    std::string pedido_to_string(const Pedido &pedido);
} // namespace presentador
