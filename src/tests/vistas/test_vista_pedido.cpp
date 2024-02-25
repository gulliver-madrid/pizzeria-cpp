#include "../../enlace_vista/presentador.h"
#include "../../modelo/dominio.h"
#include <gtest/gtest.h>

using dominio::TipoPizza;
using ContenidoPedido = std::map<TipoPizza, LineaPedido>;

TEST(VistaPedido, NumLineas) {
    ContenidoPedido contenido(
        {{TipoPizza::Margarita, {2, 5}}, //
         {TipoPizza::Pepperoni, {1, 4}}}
    );
    Pedido pedido(std::move(contenido));
    const auto vista_pedido = presentador::impl::pedido_to_vista(pedido);
    auto result = vista_pedido.get_num_lineas();
    ASSERT_EQ(2, result);
}

TEST(VistaPedido, NoEstaCubiertoSiNingunaLineaEstaCubierta) {
    ContenidoPedido contenido(
        {{TipoPizza::Margarita, {2, 5}}, //
         {TipoPizza::Pepperoni, {1, 4}}}
    );
    Pedido pedido(std::move(contenido));
    const auto vista_pedido = presentador::impl::pedido_to_vista(pedido);
    auto result = vista_pedido.esta_cubierto();
    ASSERT_EQ(false, result);
}

TEST(VistaPedido, NoEstaCubiertoAunqueHayaLineasCubiertas) {
    ContenidoPedido contenido(
        {{TipoPizza::Margarita, {5, 5}}, //
         {TipoPizza::Pepperoni, {1, 4}}}
    );
    Pedido pedido(std::move(contenido));
    const auto vista_pedido = presentador::impl::pedido_to_vista(pedido);
    auto result = vista_pedido.esta_cubierto();
    ASSERT_EQ(false, result);
}

TEST(VistaPedido, EstaCubierto) {
    ContenidoPedido contenido(
        {{TipoPizza::Margarita, {5, 5}}, //
         {TipoPizza::Pepperoni, {4, 4}}}
    );
    Pedido pedido(std::move(contenido));
    const auto vista_pedido = presentador::impl::pedido_to_vista(pedido);
    auto result = vista_pedido.esta_cubierto();
    ASSERT_EQ(true, result);
}
