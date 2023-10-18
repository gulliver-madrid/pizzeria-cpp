#include "boton_con_texto.h"
#include "varios.h"
#include <cassert>

namespace medidas {
    constexpr int MARGEN_BOTON = 20;
    constexpr int TAMANO_TEXTO_BOTONES = 32;
} // namespace medidas

size_t BotonConTexto::proximo_id = 1;

/*
 * Debe ser llamado en todos los constructores para garantizar que ningun boton
 * se queda sin su _id.
 */
void BotonConTexto::asignar_id() {
    if (!_id.has_value()) {
        _id = proximo_id++;
    }
}

void BotonConTexto::establecerPosicion(
    const sf::Vector2f &posicion, //
    Align align
) {
    int margen = medidas::MARGEN_BOTON * (escala * escala);
    int x;
    if (align == Align::Left) {
        x = posicion.x;
    } else {
        assert(align == Align::Right);
        x = posicion.x - forma.getGlobalBounds().width;
    }
    int y = posicion.y;
    forma.setPosition(x, y);
    // Ajustamos para evitar un margen excesivo arriba y a la izquierda
    etiqueta.setPosition(x + margen * 0.7, y + margen * 0.7);
}

BotonConTexto::BotonConTexto() { //
    asignar_id();
};

BotonConTexto::BotonConTexto(sf::RectangleShape rectShape, sf::Text txt)
    : forma(rectShape), etiqueta(txt) {
    colorBotonActivo = forma.getFillColor();
    forma.setOutlineColor(sf::Color::Black);
    forma.setOutlineThickness(2);
    asignar_id();
};

/* Crea un boton rectangular con texto sin determinar la posicion */
BotonConTexto::BotonConTexto(
    const BotonData &boton_data, //
    const sf::Font &font,        //
    double escala                //
)
    : escala(escala) {
    // La escala del margen es proporcional al cuadrado de la escala del botón
    int margen = medidas::MARGEN_BOTON * (escala * escala);
    // Primero creamos la etiqueta para usar sus límites en el Rect
    etiqueta = crearEtiqueta(
        medidas::TAMANO_TEXTO_BOTONES * escala, boton_data.color_texto, font
    );
    etiqueta.setString(boton_data.texto);
    sf::FloatRect textRect = etiqueta.getGlobalBounds();

    forma.setSize(
        sf::Vector2f(textRect.width + margen * 2, textRect.height + margen * 2)
    );
    forma.setFillColor(boton_data.color_fondo);
    asignar_id();
};
/* Crea un boton rectangular con texto */
BotonConTexto::BotonConTexto(
    const BotonData &boton_data,  //
    const sf::Vector2f &posicion, //
    const sf::Font &font,         //
    Align align,                  //
    double escala                 //
)
    : BotonConTexto(boton_data, font, escala) {
    establecerPosicion(posicion, align);
    asignar_id();
};

/*
 * Solo se detectará la colisión si el botón está visible y activo
 */
bool BotonConTexto::colisiona(const sf::Vector2i &mousePos) const {
    if (!visible || !activo)
        return false;
    return forma.getGlobalBounds().contains(
        static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)
    );
}

void BotonConTexto::dibujar(sf::RenderWindow &window) {
    if (!visible)
        return;
    if (!colorBotonActivo.has_value())
        colorBotonActivo = forma.getFillColor();
    if (activo) {
        forma.setFillColor(colorBotonActivo.value());
    } else {
        forma.setFillColor(sf::Color(100, 100, 100));
    }
    window.draw(forma);
    window.draw(etiqueta);
}

/**
 * Activa el botón solo si está actualmente inactivo.
 */
void BotonConTexto::activar() {
    if (!activo)
        activo = true;
}

/**
 * Desactiva el botón solo si está actualmente activo.
 */
void BotonConTexto::desactivar() {
    if (activo)
        activo = false;
}

void BotonConTexto::activacion_condicional(bool condicion) {
    if (condicion) {
        activar();
    } else {
        desactivar();
    }
}
size_t BotonConTexto::get_id() const { //
    assert(_id.has_value());
    return _id.value();
}

bool BotonConTexto::esta_activo() const { //
    return activo;
}
