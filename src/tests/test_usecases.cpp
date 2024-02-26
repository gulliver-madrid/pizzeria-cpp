#include "../datos_niveles.h"
#include "../globales.h"
#include "../juego.h"
#include "../modelo_amplio/aplicador.h"
#include "../modelo_amplio/comandos.h"
#include "../motor_nivel.h"
#include "../setup_juego.h"
#include "../vista/basicos_vista.h"
#include "../vista/paneles.h"
#include "../vista/vista.h"
#include <gtest/gtest.h>

int obtener_numero_barras_progreso(MotorNivel &nivel) {
    auto vista = nivel.get_vista();
    auto vista_ = std::dynamic_pointer_cast<Vista>(vista);
    assert(vista_);
    auto paneles = vista_->get_paneles();
    auto paneles_ = std::dynamic_pointer_cast<const Paneles>(paneles);
    assert(paneles_);
    auto panel_en_preparacion =
        paneles_->getPanel(IndicePanel::PANEL_EN_PREPARACION);
    auto panel_en_preparacion_ =
        std::dynamic_pointer_cast<PanelEnPreparacion>(panel_en_preparacion);
    assert(panel_en_preparacion_);
    return panel_en_preparacion_->barras_progreso_con_nombres.size();
}

// Al iniciar un nuevo nivel y entrar en modo instrucciones,
// los paneles no se estaran mostrando.

// Debe poderse construir un nivel sin Globales ni Grid
// Debe poderse establecer la fase inicial como MostrandoInstrucciones

TEST(Usecases, EnModoInstruccionesNoSeMuestranLosPaneles) { //
    MotorNivel nivel;
    nivel.establecer_fase(FaseNivel::MostrandoInstrucciones);
    auto paneles = nivel.get_vista()->get_paneles();
    ASSERT_EQ(paneles->get_visibilidad(), false);
}

TEST(Usecases, AlEmpezarJuegoSeMuestranLosPaneles) { //
    MotorNivel nivel;
    nivel.establecer_fase(FaseNivel::MostrandoInstrucciones);
    nivel.setup();

    nivel.aplica_comando(Comando::Empezar());

    // en este caso el tiempo es irrelevante
    nivel.actualizar_interfaz_grafico();
    auto paneles = nivel.get_vista()->get_paneles();
    ASSERT_EQ(paneles->get_visibilidad(), true);
}

TEST(Usecases, AlEncargarUnaPizzaApareceUnaBarraDeProgreso) {
    MotorNivel nivel;
    nivel.establecer_fase(FaseNivel::MostrandoInstrucciones);
    nivel.setup();

    nivel.aplica_comando(Comando::Empezar());
    nivel.actualizar_interfaz_grafico();
    ASSERT_EQ(obtener_numero_barras_progreso(nivel), 0);

    nivel.aplica_comando(Comando::Encargar{dominio::TipoPizza::Margarita});

    nivel.actualizar_interfaz_grafico();
    ASSERT_EQ(obtener_numero_barras_progreso(nivel), 1);
}

// TODO: crear test de que las lineas de los pedidos muestren si estan completas
