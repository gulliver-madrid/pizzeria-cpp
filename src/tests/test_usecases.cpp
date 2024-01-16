#include "../datos_niveles.h"
#include "../globales.h"
#include "../juego.h"
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
