#include "globales.h"
#include "vista/componentes/boton_con_texto.h"

bool Globales::detecta_colision(
    std::shared_ptr<BotonConTexto> boton, const sf::Vector2i &mouse_pos
) {
    bool hay_colision = boton->colisiona(mouse_pos);
    if (hay_colision) {
        const auto id_boton = boton->get_id();
        sf::Sound &sound = sounds[id_boton];
        if (button_click_buffer) {
            sound.setBuffer(button_click_buffer.value());
            sound.play();
        }
    }
    return hay_colision;
}
