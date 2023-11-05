#include "boton_con_texto.h"
#include "varios.h"
#include <cassert>
#include <iostream>

namespace medidas {
    constexpr int MARGEN_BOTON = 20;
    constexpr int TAMANO_TEXTO_BOTONES = TAMANO_TEXTO_GRANDE;
} // namespace medidas

struct Posicionamiento {
    sf::FloatRect rect_padre;
    sf::Vector2f posicion_relativa;
    Align alineamiento = Align::Left;

    std::pair<sf::Vector2f, sf::Vector2f>
    calcular_posicion_absoluta(const double escala, const float forma_width);
};

std::pair<sf::Vector2f, sf::Vector2f>
Posicionamiento::calcular_posicion_absoluta(
    const double escala, const float forma_width
) {
    const sf::Vector2f posicion = posicion_relativa;
    const Align align = alineamiento;
    const int margen = medidas::MARGEN_BOTON * (escala * escala);
    int x;
    if (align == Align::Left) {
        x = rect_padre.left + posicion.x;
    } else {
        assert(align == Align::Right);
        // Aqui la posicion relativa se refiere desde el lado derecho del padre
        x = rect_padre.left + rect_padre.width + posicion.x - forma_width;
    }
    const int y = rect_padre.getPosition().y + posicion.y;
    return {
        sf::Vector2f(x, y),
        // Ajustamos para evitar un margen excesivo arriba y a la izquierda
        sf::Vector2f(x + margen * 0.7, y + margen * 0.7)
    };
}

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

BotonConTexto &BotonConTexto::operator=(BotonConTexto &&) noexcept = default;
BotonConTexto::BotonConTexto(BotonConTexto &&otro) noexcept = default;
BotonConTexto::~BotonConTexto() = default;

void BotonConTexto::_calcular_posicion_absoluta() {
    // esta posicion estara a la derecha o a la izquierda de acuerdo con el
    // alineamiento
    const auto [pos_forma, pos_etiqueta] =
        posicionamiento->calcular_posicion_absoluta(
            escala, forma.getGlobalBounds().width
        );

    forma.setPosition(pos_forma);
    etiqueta.setPosition(pos_etiqueta);
}

void BotonConTexto::establecer_rect_padre(const sf::FloatRect &rect) {
    posicionamiento->rect_padre = rect;
    _calcular_posicion_absoluta();
}

void BotonConTexto::establecerPosicion(
    const sf::Vector2f &posicion, //
    const Align align
) {
    posicionamiento->alineamiento = align;
    posicionamiento->posicion_relativa = posicion;
    _calcular_posicion_absoluta();
}

BotonConTexto::BotonConTexto() { //
    std::cout << "En constructor sencillo" << std::endl;
    posicionamiento = std::make_unique<Posicionamiento>();
    asignar_id();
};

BotonConTexto::BotonConTexto(sf::RectangleShape rectShape, sf::Text txt)
    : forma(rectShape), etiqueta(txt) {
    std::cout << "En constructor de 2" << std::endl;
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
    : BotonConTexto() {
    std::cout << "En constructor de 3" << std::endl;
    this->escala = escala;
    // La escala del margen es proporcional al cuadrado de la escala del botón
    int margen = medidas::MARGEN_BOTON * (escala * escala);
    // Primero creamos la etiqueta para usar sus límites en el Rect
    etiqueta = crearEtiqueta(
        boton_data.texto, medidas::TAMANO_TEXTO_BOTONES * escala,
        boton_data.color_texto, font
    );
    sf::FloatRect textRect = etiqueta.getGlobalBounds();

    forma.setSize(
        sf::Vector2f(textRect.width + margen * 2, textRect.height + margen * 2)
    );
    forma.setFillColor(boton_data.color_fondo);
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
    std::cout << "En constructor de 5" << std::endl;
    establecerPosicion(posicion, align);
};

/*
 * Solo se detectara la colision si el boton esta visible y activo
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
