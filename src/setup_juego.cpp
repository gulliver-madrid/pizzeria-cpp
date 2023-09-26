#include "setup_juego.h"
#include "cadenas.h"
#include "manejo_rutas.h"
#include "paths.h"
#include "vista/vista_data.h"
#include <cassert>
#include <unordered_set>

PedidosEstaticos construir_pedidos(std::vector<DatosNivelTipoPizza> datos) {
    std::map<TipoPizza, DatosNivelTipoPizza> pedidos;
    std::unordered_set<TipoPizza> anadidos;
    for (auto dato : datos) {
        assert(anadidos.find(dato.tipo) == anadidos.end());
        pedidos[dato.tipo] = dato;
        anadidos.insert(dato.tipo);
    }
    return {pedidos};
}

// Inicia los elementos del juego que permanecerán entre niveles
// Inicializa las variables globales window, font y buffer
// Devuelve un booleano indicando si se completo con exito
bool setup_juego(Globales &globales) {
    std::string title = TITLE;
    globales.window.create(
        sf::VideoMode(TAMANO_INICIAL_VENTANA), interpolar_unicode(title)
    );
    globales.window.setFramerateLimit(FPS);

    if (!globales.font.loadFromFile(getResourcePath(FONT_PATH).string()))
        return false;

    {
        sf::SoundBuffer buffer;
        if (buffer.loadFromFile(getResourcePath(SUCCESS_SOUND_PATH).string()))
            globales.success_buffer = buffer;
    }

    {
        sf::SoundBuffer buffer;
        if (buffer.loadFromFile(
                getResourcePath(BUTTON_CLICK_SOUND_PATH).string()
            ))
            globales.button_click_buffer = buffer;
    }

    if (globales.music.openFromFile(getResourcePath(MUSIC_PATH).string())) {
        globales.music.setVolume(50);
        globales.music.play();
    }
    return true;
}
