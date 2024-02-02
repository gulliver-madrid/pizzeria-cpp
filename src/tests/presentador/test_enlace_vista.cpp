#include "../../enlace_vista/enlace_vista.h"
#include <gtest/gtest.h>

TEST(EnlaceVista, CreacionEnlaceVista) {
    EnlaceVista enlace_vista;
    ASSERT_EQ(
        enlace_vista.get_presentacion_vista().visibilidad.instrucciones, false
    );
    ASSERT_EQ(
        enlace_vista.get_presentacion_vista().visibilidad.resultado, false
    );
}
