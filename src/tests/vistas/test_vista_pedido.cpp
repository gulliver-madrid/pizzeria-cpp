#include "../../enlace_vista/presentador.h"
#include "../../modelo/dominio.h"
#include <gtest/gtest.h>
#include <map>

using dominio::TipoPizza;
using ContenidoPedido = std::map<TipoPizza, LineaPedido>;
using Pair = std::pair<int, int>;

Pedido crear_pedido_prueba(Pair margarita, Pair pepperoni) {
    ContenidoPedido contenido;
    contenido[TipoPizza::Margarita] =
        LineaPedido{margarita.first, margarita.second};
    contenido[TipoPizza::Pepperoni] =
        LineaPedido{pepperoni.first, pepperoni.second};

    Pedido pedido(std::move(contenido));
    return pedido;
}

TEST(VistaPedido, NumLineas) {
    const auto pedido = crear_pedido_prueba({2, 5}, {1, 4});
    const auto vista_pedido = presentador::impl::pedido_to_vista(pedido);
    auto result = vista_pedido.get_num_lineas();
    ASSERT_EQ(2, result);
}

void comprobar_caso(Pair margarita, Pair pepperoni, bool estaCubiertoEsperado) {
    const auto pedido = crear_pedido_prueba(margarita, pepperoni);
    const auto vista_pedido = presentador::impl::pedido_to_vista(pedido);
    ASSERT_EQ(estaCubiertoEsperado, vista_pedido.esta_cubierto());
}

TEST(VistaPedido, NoEstaCubiertoSiNingunaLineaEstaCubierta) {
    comprobar_caso({2, 5}, {1, 4}, false);
}

TEST(VistaPedido, NoEstaCubiertoAunqueHayaLineasCubiertas) {
    comprobar_caso({5, 5}, {1, 4}, false);
}

TEST(VistaPedido, EstaCubierto) { //
    comprobar_caso({5, 5}, {4, 4}, true);
}
