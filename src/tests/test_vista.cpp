#include "../vista/vista.h"
#include <gtest/gtest.h>

TEST(Vista, AlCrearVistaLasInstruccionesYResultadoNoSeMuestran) {
    Vista vista;
    ASSERT_EQ(vista.get_presentacion_vista()->visibilidad.instrucciones, false);
    ASSERT_EQ(vista.get_presentacion_vista()->visibilidad.resultado, false);
}
