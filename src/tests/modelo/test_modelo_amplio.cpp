
#include "../../comandos.h"
#include "../../datos_nivel.h"
#include "../../general.h"
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

TEST(ModeloAmplio, ModeloAmplioAplicaComandoSalir) {
    const std::string instrucciones = "test instrucciones";
    const DatosNivel datos_nivel;
    ModeloAmplio modelo_amplio(datos_nivel);
    const auto result = modelo_amplio.aplica_comando(Comando::Salir{});
    EXPECT_EQ(result, FaseNivel::Saliendo);
}

TEST(ModeloAmplio, ModeloAmplioAplicaComandoEncargarPizza) {
    using dominio::TipoPizza;
    const std::string instrucciones = "test instrucciones";
    const DatosNivel datos_nivel;
    ModeloAmplio modelo_amplio(datos_nivel);
    modelo_amplio.estado.fase_actual = FaseNivel::Activa;
    const std::optional<FaseNivel> result =
        modelo_amplio.aplica_comando(Comando::Encargar{TipoPizza::Margarita});
    EXPECT_EQ(modelo_amplio.estado.estado_modelo.encargos.total(), 1);
}
