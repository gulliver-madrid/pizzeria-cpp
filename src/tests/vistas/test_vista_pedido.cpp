#include "../../enlace_vista/presentador.h"
#include "../../modelo/dominio.h"
#include <gtest/gtest.h>

using dominio::TipoPizza;

TEST(VistaPedido, NumLineas) {
    std::map<TipoPizza, LineaPedido> contenido(
        {{TipoPizza::Margarita, {2, 5}}, //
         {TipoPizza::Pepperoni, {1, 4}}}
    );
    Pedido pedido(std::move(contenido));
    const auto vista_pedido = presentador::impl::pedido_to_vista(pedido);
    auto result = vista_pedido.get_num_lineas();
    ASSERT_EQ(2, result);
}
