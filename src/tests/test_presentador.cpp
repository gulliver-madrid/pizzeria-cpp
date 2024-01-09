#include "../modelo/datos_nivel_para_modelo.h"
#include "../modelo/dominio.h"
#include "../modelo/estado_modelo.h"
#include "../modelo/modelo.h"
#include "../vista/enlace_vista.h"
#include "../vista/presentador.h"
#include "../vista/vista.h"
#include <gtest/gtest.h>

using dominio::TipoPizza;

TEST(Presentador, LineaCompletitudPizza) {
    auto result =
        presentador::crea_linea_completitud_pizza(TipoPizza::Margarita, 2, 5);
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

TEST(Presentador, ObtenerActivacionBotonesSiPedidosEstaVacio) {
    // No habria botones despachar al no haber pedidos
    // que hagan referencia a ningun tipo de pizza
    // Y cualquier boton encargar estaria activo al no haber
    // demasiadas pizzas en el area de preparadas
    DatosNivelParaModelo datos_nivel_para_modelo({});
    EstadoModelo estado_modelo(datos_nivel_para_modelo);
    const auto activacion_botones =
        impl::obtener_activacion_botones(estado_modelo);
    ASSERT_TRUE(activacion_botones.despachar.empty());
    ASSERT_EQ(activacion_botones.encargar, true);
}
