#include "../../modelo/datos_modelo_interno.h"
#include "../../modelo/dominio.h"
#include "../../modelo/modelo_interno.h"
#include "../../vista/enlace_vista.h"
#include "../../vista/vista.h"
#include <cassert>
#include <gtest/gtest.h>

using namespace enlace_vista_impl;
using dominio::TipoPizza;
using modelo::Pedidos;
using PizzaToBool = std::map<TipoPizza, bool>;

// Crea un modelo interno a partir de un conjunto de pedidos
ModeloInterno crear_modelo_interno(modelo::Pedidos pedidos) {
    DatosModeloInterno datos_modelo_interno(pedidos);
    ModeloInterno modelo(datos_modelo_interno);
    return modelo;
}
Pedidos crear_pedidos_margarita(unsigned int num_pizzas) {
    return {Pedido({{TipoPizza::Margarita, num_pizzas}})};
}

TEST(Presentador, ActivacionBotonesCorrectaSiPedidosEstaVacio) {
    ModeloInterno modelo = crear_modelo_interno({});
    const auto activacion = obtener_activacion_botones(modelo);

    // No debe haber botones despachar al no haber pedidos
    // que hagan referencia a ningun tipo de pizza
    ASSERT_TRUE(activacion.despachar.empty());

    // Cualquier boton encargar estaria activo al no haber
    // demasiadas pizzas en preparacion
    ASSERT_EQ(activacion.encargar, true);
}

TEST(
    Presentador, BotonesDespacharDesactivadosSiHayDemasiadosPedidosSimultaneos
) {
    Pedidos pedidos = crear_pedidos_margarita(4);
    ModeloInterno modelo = crear_modelo_interno(pedidos);

    auto activacion = obtener_activacion_botones(modelo);
    // hay un boton despachar desactivado
    PizzaToBool expected = {{TipoPizza::Margarita, false}};
    ASSERT_EQ(activacion.despachar, expected);

    // Verifica el estado de activacion de los botones encargar
    assert(modelo_info::MAXIMO_PIZZAS_EN_PREPARACION == 3);
    for (int i = 0; i < 3; i++) {
        // Mientras no llega al maximo el boton estara activado
        activacion = obtener_activacion_botones(modelo);
        ASSERT_EQ(activacion.encargar, true);
        modelo.anadir_encargo(TipoPizza::Margarita);
    }

    // Tras encargar la ultima no es posible encargar mas
    activacion = obtener_activacion_botones(modelo);
    ASSERT_EQ(activacion.encargar, false);
}

TEST(Presentador, BotonDespacharDesctivadoConPizzaNoPreparada) {
    Pedidos pedidos = crear_pedidos_margarita(2);
    ModeloInterno modelo = crear_modelo_interno(pedidos);

    auto activacion = obtener_activacion_botones(modelo);
    // hay un boton despachar desactivado
    PizzaToBool expected = {{TipoPizza::Margarita, false}};
    ASSERT_EQ(activacion.despachar, expected);
}

TEST(Presentador, UnBotonDespacharActivadoSiHayUnaPizzaPreparada) {
    Pedidos pedidos = crear_pedidos_margarita(2);
    ModeloInterno modelo = crear_modelo_interno(pedidos);

    modelo.gestor_tiempo.activar();
    modelo.anadir_encargo(TipoPizza::Margarita);
    modelo.gestor_tiempo.tick(sf::seconds(10));
    modelo.evaluar_preparacion_pizzas();

    auto activacion = obtener_activacion_botones(modelo);
    PizzaToBool expected = {{TipoPizza::Margarita, true}};
    ASSERT_EQ(activacion.despachar, expected);
}
