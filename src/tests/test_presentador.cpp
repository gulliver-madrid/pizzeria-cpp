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

TEST(Presentador, ObtenerActivacionBotonesSiHayDemasiadosPedidosSimultaneos) {
    modelo::Pedidos pedidos = {Pedido({{TipoPizza::Margarita, 4}})};
    DatosNivelParaModelo datos_nivel_para_modelo(pedidos);
    EstadoModelo estado_modelo(datos_nivel_para_modelo);
    auto activacion_botones = impl::obtener_activacion_botones(estado_modelo);
    // hay un boton despachar desactivado
    ASSERT_EQ(activacion_botones.despachar.size(), 1);
    ASSERT_EQ(activacion_botones.despachar.at(TipoPizza::Margarita), false);

    // Verifica el estado de activacion de los botones encargar
    assert(modelo_info::MAXIMO_PIZZAS_EN_PREPARACION == 3);
    for (int i = 0; i < 3; i++) {
        // Mientras no llega al maximo el boton estara activado
        activacion_botones = impl::obtener_activacion_botones(estado_modelo);
        ASSERT_EQ(activacion_botones.encargar, true);
        estado_modelo.anadir_encargo(TipoPizza::Margarita);
    }

    // Tras encargar la ultima no es posible encargar mas
    activacion_botones = impl::obtener_activacion_botones(estado_modelo);
    ASSERT_EQ(activacion_botones.encargar, false);
}

TEST(Presentador, ObtenerActivacionBotonesSiHayUnaPizzaPreparada) {
    modelo::Pedidos pedidos = {Pedido({{TipoPizza::Margarita, 2}})};
    DatosNivelParaModelo datos_nivel_para_modelo(pedidos);
    EstadoModelo estado_modelo(datos_nivel_para_modelo);
    auto activacion_botones = impl::obtener_activacion_botones(estado_modelo);
    // hay un boton despachar desactivado
    ASSERT_EQ(activacion_botones.despachar.size(), 1);
    ASSERT_EQ(activacion_botones.despachar.at(TipoPizza::Margarita), false);

    estado_modelo.gestor_tiempo.activar();

    estado_modelo.anadir_encargo(TipoPizza::Margarita);
    estado_modelo.gestor_tiempo.tick(sf::seconds(10));
    estado_modelo.evaluar_preparacion_pizzas();

    activacion_botones = impl::obtener_activacion_botones(estado_modelo);
    ASSERT_EQ(activacion_botones.despachar.size(), 1);
    ASSERT_EQ(activacion_botones.despachar.at(TipoPizza::Margarita), true);
}
