#include "setup_juego.h"
#include "globales.h"
#include "manejo_rutas.h"
#include "paths.h"
#include "vista/cadenas.h"
#include "vista/vista_data.h"
#include <cassert>
#include <iostream>
#include <unordered_set>

// Inicia los elementos del juego que permaneceran entre niveles
// Inicializa las variables globales window, font y buffer
// Devuelve un booleano indicando si se completo con exito
bool setup_juego(std::shared_ptr<Globales> globales) {
    std::cout << "En setup_juego" << std::endl;
    assert(globales);
    std::string title = TITLE;
    std::cout << "Creando ventana" << std::endl;
    globales->window.create(
        sf::VideoMode(TAMANO_INICIAL_VENTANA), interpolar_unicode(title)
    );
    globales->window.setFramerateLimit(FPS);

    std::cout << "Anadiendo Font" << std::endl;

    if (!globales->font->loadFromFile(getResourcePath(FONT_PATH).string()))
        return false;

    std::cout << "Font anadida" << std::endl;
    {
        sf::SoundBuffer buffer;
        if (buffer.loadFromFile(getResourcePath(SUCCESS_SOUND_PATH).string()))
            globales->success_buffer = buffer;
    }

    std::cout << "Cargando mas recursos" << std::endl;

    {
        sf::SoundBuffer buffer;
        if (buffer.loadFromFile(
                getResourcePath(BUTTON_CLICK_SOUND_PATH).string()
            ))
            globales->button_click_buffer = buffer;
    }

    if (globales->music.openFromFile(getResourcePath(MUSIC_PATH).string())) {
        globales->music.setVolume(50);
        globales->music.setLoop(true);
        globales->music.play();
    }
    return true;
}
