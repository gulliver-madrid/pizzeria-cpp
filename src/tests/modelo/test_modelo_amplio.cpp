
#include "../../datos_nivel.h"
#include "../../fase_nivel.h"
#include "../../modelo_amplio/aplicador.h"
#include "../../modelo_amplio/comandos.h"
#include "../../modelo_amplio/modelo_amplio.h"
#include <cassert>
#include <gtest/gtest.h>

// Tests de ModeloAmplio
TEST(ModeloAmplio, ModeloAmplioEmpiezaMostrandoInstrucciones) {
    const std::string instrucciones = "test instrucciones";
    const DatosNivel datos_nivel;
    ModeloAmplio modelo_amplio(datos_nivel.datos_modelo_interno);
    EXPECT_EQ(
        modelo_amplio.get_fase_actual(), FaseNivel::MostrandoInstrucciones
    );
}

TEST(ModeloAmplio, ModeloAmplioAplicaComandoSalir) {
    const std::string instrucciones = "test instrucciones";
    const DatosNivel datos_nivel;
    ModeloAmplio modelo_amplio(datos_nivel.datos_modelo_interno);
    const auto result = aplica_comando(modelo_amplio, Comando::Salir{});
    EXPECT_EQ(result, FaseNivel::Saliendo);
}

TEST(ModeloAmplio, ModeloAmplioAplicaComandoEncargarPizza) {
    using dominio::TipoPizza;
    const std::string instrucciones = "test instrucciones";
    const DatosNivel datos_nivel;
    ModeloAmplio modelo_amplio(datos_nivel.datos_modelo_interno);
    modelo_amplio.fase_actual = FaseNivel::Activa;
    const std::optional<FaseNivel> result =
        aplica_comando(modelo_amplio, Comando::Encargar{TipoPizza::Margarita});
    EXPECT_EQ(modelo_amplio.modelo_interno.encargos.total(), 1);
}
