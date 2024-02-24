#include "../../enlace_vista/enlace_vista.h"
#include "../../modelo/datos_modelo_interno.h"
#include "../../modelo/dominio.h"
#include "../../modelo/modelo_info.h"
#include "../../modelo/modelo_interno.h"
#include "../../vista/vista.h"
#include <cassert>
#include <gtest/gtest.h>

using namespace enlace_vista_impl;
using dominio::TipoPizza;
using modelo::Pedidos;
using PizzaToBool = std::map<TipoPizza, bool>;

// Estos tests chequean la creacion correcta de ActivacionBotones
// en varios escenarios

// Crea un modelo interno a partir de un conjunto de pedidos
ModeloInterno crear_modelo_interno(modelo::Pedidos pedidos) {
    DatosModeloInterno datos_modelo_interno(pedidos);
    ModeloInterno modelo(datos_modelo_interno);
    return modelo;
}
Pedidos crear_pedidos_margarita(UInt num_pizzas) {
    return {Pedido({{TipoPizza::Margarita, num_pizzas}})};
}

///// ActivacionTest /////

class ActivacionTest : public testing::Test {
  private:
    ActivacionBotones _obtener_activacion() {
        return obtener_activacion_botones(_modelo.value());
    }

  protected:
    std::optional<ModeloInterno> _modelo;
    void _crear_modelo(Pedidos pedidos) {
        _modelo.emplace(crear_modelo_interno(pedidos));
    }

    void _assert_activacion_encargar(bool expected) {
        auto activacion = _obtener_activacion();
        ASSERT_EQ(activacion.encargar, expected);
    }
    void _assert_despachar_eq(PizzaToBool expected) {
        auto activacion = _obtener_activacion();
        ASSERT_EQ(activacion.despachar, expected);
    }
};

TEST_F(ActivacionTest, ActivacionBotonesCorrectaSiPedidosEstaVacio) {
    _crear_modelo({});

    // No debe haber botones despachar al no haber pedidos
    // que hagan referencia a ningun tipo de pizza
    _assert_despachar_eq({});

    // Cualquier boton encargar estaria activo al no haber
    // demasiadas pizzas en preparacion
    _assert_activacion_encargar(true);
}

TEST_F(
    ActivacionTest,
    BotonesDespacharDesactivadosSiHayDemasiadosPedidosSimultaneos
) {
    const auto maximo = modelo_info::MAXIMO_PIZZAS_EN_PREPARACION;
    Pedidos pedidos = crear_pedidos_margarita(maximo + 1);
    _crear_modelo(pedidos);

    // Verifica el estado de activacion de los botones encargar
    for (int i = 0; i < maximo; ++i) {
        // Mientras no llega al maximo el boton estara activado
        _assert_activacion_encargar(true);
        _modelo.value().anadir_encargo(TipoPizza::Margarita);
    }

    // Tras encargar la ultima no es posible encargar mas
    _assert_activacion_encargar(false);
}

///// ActivacionConPedidoDosMargaritasTest /////

class ActivacionConPedidoDosMargaritasTest : public ActivacionTest {
  protected:
    void SetUp() override {
        Pedidos pedidos = crear_pedidos_margarita(2);
        _crear_modelo(pedidos);
    }
    void preparar_pizza() {
        // Encarga una pizza y pasa el tiempo para prepararla
        assert(_modelo.has_value());
        auto &modelo = _modelo.value();
        modelo.gestor_tiempo_juego->activar();
        modelo.anadir_encargo(TipoPizza::Margarita);
        modelo.gestor_tiempo_juego->tick(sf::seconds(10));
        modelo.evaluar_preparacion_pizzas();
    }
};

TEST_F(
    ActivacionConPedidoDosMargaritasTest,
    BotonDespacharDesactivadoConPizzaNoPreparada
) {
    _assert_despachar_eq({{TipoPizza::Margarita, false}});
}

TEST_F(
    ActivacionConPedidoDosMargaritasTest,
    BotonDespacharActivadoSiHayUnaPizzaPreparada
) {
    preparar_pizza();
    _assert_despachar_eq({{TipoPizza::Margarita, true}});
}
