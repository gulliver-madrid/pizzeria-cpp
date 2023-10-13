#include "../modelo/dominio.h"
#include "../modelo/modelo.h"
#include "../vista/presentador.h"
#include <gtest/gtest.h>

TEST(Presentador, LineaCompletitudPizza) {
    auto result =
        presentador::crea_linea_completitud_pizza(TipoPizza::Margarita, 2, 5);
    ASSERT_EQ(result, "Margarita: 2/5");
}

TEST(Presentador, PedidoToString) {
    std::map<TipoPizza, PedidoTipoPizza> contenido(
        {{TipoPizza::Margarita, {2, 5}}, {TipoPizza::Pepperoni, {1, 4}}}
    );
    Pedido pedido(contenido);

    auto result = presentador::pedido_to_string(pedido);
    ASSERT_EQ(result, "Margarita: 2/5\nPepperoni: 1/4");
}
