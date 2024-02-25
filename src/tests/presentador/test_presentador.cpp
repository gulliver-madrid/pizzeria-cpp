#include "../../enlace_vista/presentador.h"
#include "../../modelo/datos_modelo_interno.h"
#include "../../modelo/dominio.h"
#include "../../vista/vista.h"
#include <SFML/System/Time.hpp>
#include <gtest/gtest.h>

using dominio::TipoPizza;

TEST(Presentador, LineaCompletitudPizza) {
    auto vista_linea = presentador::impl::crea_vista_linea(
        TipoPizza::Margarita, 2, 5 //
    );
    auto result = vista_linea.cadena;
    ASSERT_EQ("Margarita: 2/5", result);
}

TEST(Presentador, PedidoToString) {
    std::map<TipoPizza, LineaPedido> contenido(
        {{TipoPizza::Margarita, {2, 5}}, {TipoPizza::Pepperoni, {1, 4}}}
    );
    Pedido pedido(std::move(contenido));
    const auto vista_pedido = presentador::impl::pedido_to_vista(pedido);
    const auto &result = vista_pedido.obtener_cadena_completa();
    ASSERT_EQ("Margarita: 2/5\nPepperoni: 1/4", result);
}

TEST(Presentador, ContadoresToPreparadasString) {
    modelo::PizzasAContadores contadores = {{TipoPizza::Margarita, Contadores{}}
    };
    contadores.at(TipoPizza::Margarita).preparadas++;
    const auto info_preparadas =
        presentador::contadores_to_preparadas(contadores);
    const auto &result = info_preparadas.at(TipoPizza::Margarita);
    ASSERT_EQ("Margarita: 1", result);
}

TEST(Presentador, CreaTextoEtiquetaBarraEstado) {
    const auto tiempo_real = sf::seconds(62);
    const auto tiempo_juego = sf::seconds(35);
    const auto vista_barra_estado =
        presentador::crea_vista_barra_estado(tiempo_real, tiempo_juego);
    const auto &result = vista_barra_estado.texto.value;
    ASSERT_EQ("Tiempo Juego: 00:35       Tiempo Real: 01:02", result);
}
