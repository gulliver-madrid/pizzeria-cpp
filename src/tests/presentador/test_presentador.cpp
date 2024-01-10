#include "../../modelo/datos_modelo_interno.h"
#include "../../modelo/dominio.h"
#include "../../vista/presentador.h"
#include "../../vista/vista.h"
#include <gtest/gtest.h>

using dominio::TipoPizza;

TEST(Presentador, LineaCompletitudPizza) {
    auto result = presentador::crea_linea_completitud_pizza(
        TipoPizza::Margarita, 2, 5 //
    );
    ASSERT_EQ(result, "Margarita: 2/5");
}

TEST(Presentador, PedidoToString) {
    std::map<TipoPizza, PedidoTipoPizza> contenido(
        {{TipoPizza::Margarita, {2, 5}}, {TipoPizza::Pepperoni, {1, 4}}}
    );
    Pedido pedido(std::move(contenido));
    auto result = presentador::pedido_to_string(pedido);
    ASSERT_EQ(result, "Margarita: 2/5\nPepperoni: 1/4");
}

TEST(Presentador, ContadoresToPreparadasString) {
    modelo::PizzasAContadores contadores;

    contadores.emplace(TipoPizza::Margarita, Contadores{});
    contadores.at(TipoPizza::Margarita).preparadas++;
    auto vista_preparadas = impl::contadores_to_preparadas(contadores);
    ASSERT_EQ(vista_preparadas.at(TipoPizza::Margarita), "Margarita: 1");
}
