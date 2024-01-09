#include "../modelo/datos_modelo_interno.h"
#include "../modelo/dominio.h"
#include "../modelo/modelo.h"
#include "../modelo/modelo_interno.h"
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
    DatosModeloInterno datos_modelo_interno({});
    ModeloInterno modelo_interno(datos_modelo_interno);
    const auto activacion_botones =
        impl::obtener_activacion_botones(modelo_interno);
    ASSERT_TRUE(activacion_botones.despachar.empty());
    ASSERT_EQ(activacion_botones.encargar, true);
}

TEST(Presentador, ObtenerActivacionBotonesSiHayDemasiadosPedidosSimultaneos) {
    modelo::Pedidos pedidos = {Pedido({{TipoPizza::Margarita, 4}})};
    DatosModeloInterno datos_modelo_interno(pedidos);
    ModeloInterno modelo_interno(datos_modelo_interno);
    auto activacion_botones = impl::obtener_activacion_botones(modelo_interno);
    // hay un boton despachar desactivado
    ASSERT_EQ(activacion_botones.despachar.size(), 1);
    ASSERT_EQ(activacion_botones.despachar.at(TipoPizza::Margarita), false);

    // Verifica el estado de activacion de los botones encargar
    assert(modelo_info::MAXIMO_PIZZAS_EN_PREPARACION == 3);
    for (int i = 0; i < 3; i++) {
        // Mientras no llega al maximo el boton estara activado
        activacion_botones = impl::obtener_activacion_botones(modelo_interno);
        ASSERT_EQ(activacion_botones.encargar, true);
        modelo_interno.anadir_encargo(TipoPizza::Margarita);
    }

    // Tras encargar la ultima no es posible encargar mas
    activacion_botones = impl::obtener_activacion_botones(modelo_interno);
    ASSERT_EQ(activacion_botones.encargar, false);
}

TEST(Presentador, ObtenerActivacionBotonesSiHayUnaPizzaPreparada) {
    modelo::Pedidos pedidos = {Pedido({{TipoPizza::Margarita, 2}})};
    DatosModeloInterno datos_modelo_interno(pedidos);
    ModeloInterno modelo_interno(datos_modelo_interno);
    auto activacion_botones = impl::obtener_activacion_botones(modelo_interno);
    // hay un boton despachar desactivado
    ASSERT_EQ(activacion_botones.despachar.size(), 1);
    ASSERT_EQ(activacion_botones.despachar.at(TipoPizza::Margarita), false);

    modelo_interno.gestor_tiempo.activar();

    modelo_interno.anadir_encargo(TipoPizza::Margarita);
    modelo_interno.gestor_tiempo.tick(sf::seconds(10));
    modelo_interno.evaluar_preparacion_pizzas();

    activacion_botones = impl::obtener_activacion_botones(modelo_interno);
    ASSERT_EQ(activacion_botones.despachar.size(), 1);
    ASSERT_EQ(activacion_botones.despachar.at(TipoPizza::Margarita), true);
}
