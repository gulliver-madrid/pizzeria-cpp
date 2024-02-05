#include "nivel.h"
#include "datos_nivel.h"
#include "motor_nivel.h"
#include "shared/log_init.h"
#include "shared/num_nivel.h"
#include <SFML/Window/Event.hpp>
#include <cassert>
#include <memory>
#include <optional>

///////////////////////////////////////////
// Nivel (public)
//////////////////////////////////////////

Nivel::Nivel(
    std::shared_ptr<Globales> globales,      //
    std::shared_ptr<DatosNivel> datos_nivel, //
    const NumNivelOpcional num_nivel,        //
    std::shared_ptr<Grid> grid               //
) {

    motor_nivel =
        std::make_shared<MotorNivel>(globales, datos_nivel, num_nivel, grid);
}

AccionGeneral Nivel::ejecutar() {
    assert(motor_nivel);

    motor_nivel->establecer_fase(FaseNivel::MostrandoInstrucciones);
    motor_nivel->setup();

    std::optional<AccionGeneral> accion;
    sf::Time previo = tiempo::obtener_tiempo_actual();
    LOG(info) << "Empezando bucle de juego";
    while (motor_nivel->globales->window.isOpen()) {
        LOG(info) << "Nueva iteracion del bucle de juego";
        sf::Event event;
        while (motor_nivel->globales->window.pollEvent(event)) {
            accion = motor_nivel->procesar_evento(event);
            if (accion.has_value()) {
                return accion.value();
            }
        }

        accion = motor_nivel->procesar_ciclo();
        if (accion.has_value()) {
            break;
        }

        const auto tiempo_real_actual = tiempo::obtener_tiempo_actual();
        const auto transcurrido = tiempo_real_actual - previo;
        // TODO: con hacer el tick deberia bastar para tener el tiempo real
        motor_nivel->tick(transcurrido);
        motor_nivel->actualizar_interfaz_grafico();

        previo = tiempo_real_actual;

        // TODO:unificando estas dos llamadas, globales y enlace_vista pueden
        // ser privadas
        motor_nivel->enlace_vista->dibujar_vista(motor_nivel->globales->window);
        motor_nivel->globales->window.display();
    }
    assert(accion.has_value());
    return accion.value();
}
