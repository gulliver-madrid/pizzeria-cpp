
#include "../../datos_nivel.h"
#include "../../modelo_amplio.h"
#include <cassert>
#include <gtest/gtest.h>

// Tests de ModeloAmplio

TEST(ModeloAmplio, ModeloAmplioEmpiezaMostrandoInstrucciones) {
    const std::string instrucciones = "test instrucciones";
    const DatosNivel datos_nivel;
    ModeloAmplio modelo_amplio(datos_nivel);
    EXPECT_EQ(
        modelo_amplio.get_fase_actual(), FaseNivel::MostrandoInstrucciones
    );
}
