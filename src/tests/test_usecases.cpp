#include "../datos_niveles.h"
#include "../globales.h"
#include "../juego.h"
#include "../modelo_amplio/aplicador.h"
#include "../modelo_amplio/comandos.h"
#include "../nivel.h"
#include "../setup_juego.h"
#include "../vista/vista.h"
#include <gtest/gtest.h>

// Al iniciar un nuevo nivel y entrar en modo instrucciones,
// los paneles no se estaran mostrando.

// Debe poderse construir un nivel sin Globales ni Grid
// Debe poderse establecer la fase inicial como MostrandoInstrucciones

TEST(Usecases, EnModoInstruccionesNoSeMuestranLosPaneles) { //
    Nivel nivel;
    nivel.establecer_fase(FaseNivel::MostrandoInstrucciones);
    auto paneles = nivel.get_vista()->get_paneles();
    ASSERT_EQ(paneles->get_visibilidad(), false);
}
TEST(Usecases, AlEmpezarJuegoSeMuestranLosPaneles) { //
    Nivel nivel;
    nivel.establecer_fase(FaseNivel::MostrandoInstrucciones);
    nivel.setup();
    auto result =
        aplica_comando(nivel.modelo_amplio.value(), Comando::Empezar());
    assert(result.has_value());
    nivel.procesa_cambio_de_fase(result.value());
    // en este caso el tiempo es irrelevante
    nivel.actualizar_interfaz_grafico(sf::Time::Zero);
    auto paneles = nivel.get_vista()->get_paneles();
    ASSERT_EQ(paneles->get_visibilidad(), true);
}
