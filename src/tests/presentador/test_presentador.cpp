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
    ASSERT_EQ(result, "Margarita: 2/5");
}

TEST(Presentador, PedidoToString) {
    std::map<TipoPizza, LineaPedido> contenido(
        {{TipoPizza::Margarita, {2, 5}}, {TipoPizza::Pepperoni, {1, 4}}}
    );
    Pedido pedido(std::move(contenido));
    auto result = presentador::impl::pedido_to_vista(pedido);
    ASSERT_EQ(
        result.obtener_cadena_completa(), "Margarita: 2/5\nPepperoni: 1/4"
    );
}

TEST(Presentador, ContadoresToPreparadasString) {
    modelo::PizzasAContadores contadores;

    contadores.emplace(TipoPizza::Margarita, Contadores{});
    contadores.at(TipoPizza::Margarita).preparadas++;
    auto info_preparadas = presentador::contadores_to_preparadas(contadores);
    ASSERT_EQ(info_preparadas.at(TipoPizza::Margarita), "Margarita: 1");
}

TEST(Presentador, CreaTextoEtiquetaBarraEstado) {
    const auto tiempo_real = sf::seconds(62);
    const auto tiempo_juego = sf::seconds(35);
    const auto result =
        presentador::crea_vista_barra_estado(tiempo_real, tiempo_juego);
    ASSERT_EQ(
        "Tiempo Juego: 00:35       Tiempo Real: 01:02", result.texto.value
    );
}
