#include "boton_con_texto.h"
#include "varios.h"
#include <cassert>

namespace medidas {
    constexpr int MARGEN_BOTON = 20;
    constexpr int TAMANO_TEXTO_BOTONES = TAMANO_TEXTO_GRANDE;
} // namespace medidas

///////////////////////////////////////////
// Posicionamiento
//////////////////////////////////////////

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

///////////////////////////////////////////
// BotonConTexto
//////////////////////////////////////////

size_t BotonConTexto::_proximo_id = 1;

/*
 * Debe ser llamado en todos los constructores para garantizar que ningun boton
 * se queda sin su _id.
 */
void BotonConTexto::_asignar_id() {
    if (!_id.has_value()) {
        _id = _proximo_id++;
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
            _escala, _forma.getGlobalBounds().width
        );

    _forma.setPosition(pos_forma);
    _etiqueta.setPosition(pos_etiqueta);
}

void BotonConTexto::establecer_rect_padre(const sf::FloatRect &rect) {
    posicionamiento->rect_padre = rect;
    _calcular_posicion_absoluta();
}

void BotonConTexto::establecer_posicion(
    const sf::Vector2f &posicion, //
    const Align align
) {
    posicionamiento->alineamiento = align;
    posicionamiento->posicion_relativa = posicion;
    _calcular_posicion_absoluta();
}

BotonConTexto::BotonConTexto() { //
    posicionamiento = std::make_unique<Posicionamiento>();
    _asignar_id();
};

/**
 * @brief Constructor por defecto que inicializa un boton con texto.
 *
 * Este constructor crea un boton con texto sin definir su posicion en la
 * pantalla. La apariencia del boton se escala segun el parametro proporcionado.
 *
 * @param boton_data Estructura que contiene los datos del boton como el texto,
 *                   color del texto, y color de fondo.
 * @param font Fuente utilizada para el texto del boton.
 * @param escala Factor de escala para el tamano del boton y del texto.
 */
BotonConTexto::BotonConTexto(
    const BotonData &boton_data, //
    const sf::Font &font,        //
    double escala                //
)
    : BotonConTexto() {
    this->_escala = escala;
    // La escala del margen es proporcional al cuadrado de la escala del boton
    int margen = medidas::MARGEN_BOTON * (escala * escala);
    // Primero creamos la etiqueta para usar sus limites en el Rect
    _etiqueta = crearEtiqueta(
        boton_data.texto, medidas::TAMANO_TEXTO_BOTONES * escala,
        boton_data.color_texto, font
    );
    sf::FloatRect textRect = _etiqueta.getGlobalBounds();

    _forma.setSize(
        sf::Vector2f(textRect.width + margen * 2, textRect.height + margen * 2)
    );
    _forma.setFillColor(boton_data.color_fondo);
};

/**
 * @brief Constructor sobrecargado que inicializa un boton con texto y posicion.
 *
 * Este constructor crea un boton con texto y permite definir su posicion en la
 * pantalla. La apariencia del boton se escala segun el parametro proporcionado
 * y se posiciona de acuerdo a un alineamiento especificado.
 *
 * @param boton_data Estructura que contiene los datos del boton como el texto,
 *                   color del texto, y color de fondo.
 * @param posicion Posicion inicial del boton en la pantalla.
 * @param font Fuente utilizada para el texto del boton.
 * @param align Alineamiento del boton con respecto a su posicion.
 * @param escala Factor de escala para el tamano del boton y del texto.
 */
BotonConTexto::BotonConTexto(
    const BotonData &boton_data,  //
    const sf::Vector2f &posicion, //
    const sf::Font &font,         //
    Align align,                  //
    double escala                 //
)
    : BotonConTexto(boton_data, font, escala) {
    establecer_posicion(posicion, align);
};

/**
 * @brief Comprueba si la posicion del mouse colisiona con el boton.
 *
 * Evalua si la posicion actual del cursor del mouse se encuentra dentro de los
 * limites del boton. La deteccion de colision solo ocurre si el boton esta
 * visible y activo.
 *
 * @param pos_raton Posicion actual del cursor del mouse.
 * @return true si hay colision, false en caso contrario.
 */
bool BotonConTexto::colisiona(const sf::Vector2i &pos_raton) const {
    if (!visible || !_activo)
        return false;
    return _forma.getGlobalBounds().contains(
        static_cast<float>(pos_raton.x), static_cast<float>(pos_raton.y)
    );
}

void BotonConTexto::dibujar(sf::RenderWindow &window) {
    if (!visible)
        return;
    if (!colorBotonActivo.has_value())
        colorBotonActivo = _forma.getFillColor();
    if (_activo) {
        _forma.setFillColor(colorBotonActivo.value());
    } else {
        _forma.setFillColor(sf::Color(100, 100, 100));
    }
    window.draw(_forma);
    window.draw(_etiqueta);
}

/**
 * Activa el boton solo si esta actualmente inactivo.
 */
void BotonConTexto::activar() {
    if (!_activo)
        _activo = true;
}

/**
 * Desactiva el boton solo si esta actualmente activo.
 */
void BotonConTexto::desactivar() {
    if (_activo)
        _activo = false;
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
    return _activo;
}
