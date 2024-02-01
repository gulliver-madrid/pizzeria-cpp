#include "../../modelo/datos_modelo_interno.h"
#include "../../modelo/dominio.h"
#include "../../vista/presentador.h"
#include "../../vista/vista.h"
#include <SFML/System/Time.hpp>
#include <gtest/gtest.h>

using dominio::TipoPizza;

TEST(Presentador, LineaCompletitudPizza) {
    auto result = presentador::impl::crea_linea_completitud_pizza(
        TipoPizza::Margarita, 2, 5 //
    );
    ASSERT_EQ(result, "Margarita: 2/5");
}

TEST(Presentador, PedidoToString) {
    std::map<TipoPizza, PedidoTipoPizza> contenido(
        {{TipoPizza::Margarita, {2, 5}}, {TipoPizza::Pepperoni, {1, 4}}}
    );
    Pedido pedido(std::move(contenido));
    auto result = presentador::impl::pedido_to_string(pedido);
    ASSERT_EQ(result, "Margarita: 2/5\nPepperoni: 1/4");
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
    const auto result = presentador::crea_texto_etiqueta_barra_estado(
        tiempo_real, tiempo_juego
    );
    ASSERT_EQ("Tiempo Juego: 00:35       Tiempo Real: 01:02", result);
}
