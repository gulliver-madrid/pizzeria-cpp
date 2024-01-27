#include "setup_juego.h"
#include "globales.h"
#include "manejo_rutas.h"
#include "paths.h"
#include "shared/log_init.h"
#include "vista/cadenas.h"
#include "vista/vista_data.h"
#include <cassert>
#include <unordered_set>

// Inicia los elementos del juego que permaneceran entre niveles
// Inicializa las variables globales window, font y buffer
// Devuelve un booleano indicando si se completo con exito
bool setup_juego(std::shared_ptr<Globales> globales) {
    LOG(info) << "En setup_juego";
    assert(globales);
    std::string title = TITLE;
    LOG(info) << "Creando ventana";
    globales->window.create(
        sf::VideoMode(TAMANO_INICIAL_VENTANA), interpolar_unicode(title)
    );
    globales->window.setFramerateLimit(FPS);

    LOG(info) << "Anadiendo Font";

    if (!globales->font->loadFromFile(obtener_ruta_recurso(FONT_PATH).string()))
        return false;

    LOG(info) << "Font anadida";
    {
        sf::SoundBuffer buffer;
        if (buffer.loadFromFile(
                obtener_ruta_recurso(SUCCESS_SOUND_PATH).string()
            ))
            globales->success_buffer = buffer;
    }

    LOG(info) << "Cargando mas recursos" << std::endl;

    {
        sf::SoundBuffer buffer;
        if (buffer.loadFromFile(
                obtener_ruta_recurso(BUTTON_CLICK_SOUND_PATH).string()
            ))
            globales->button_click_buffer = buffer;
    }

    if (globales->music.openFromFile(obtener_ruta_recurso(MUSIC_PATH).string()
        )) {
        globales->music.setVolume(50);
        globales->music.setLoop(true);
        globales->music.play();
    }
    return true;
}
