#include "boton_con_texto.h"
#include "../../templates/dibujar_elementos.h"
#include "varios.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <cassert>

namespace medidas {
    constexpr int MARGEN_BOTON = 20;
    constexpr int TAMANO_TEXTO_BOTONES = TAMANO_TEXTO_GRANDE;
} // namespace medidas

///////////////////////////////////////////
// Posicionamiento: declaracion
//////////////////////////////////////////

/**
 * @struct Posicionamiento
 *
 * @brief Gestiona la posician de un elemento UI respecto a un rectangulo padre.
 *
 * Esta estructura contiene informacion sobre como un elemento UI debe ser
 * posicionado en la ventana. Esto incluye el rectangulo dentro del cual el
 * elemento debe ser colocado (contenedor), la posicion relativa dentro de este
 * rectangulo y el alineamiento (izquierda o derecha).
 */
struct Posicionamiento {
  private:
    int _obtener_pos_abs_x(float ancho_forma) const;

  public:
    sf::FloatRect contenedor;
    sf::Vector2f posicion_relativa;
    Align alineamiento = Align::Left;

    std::pair<sf::Vector2f, sf::Vector2f>
    calcular_posicion_absoluta(double escala, float ancho_forma) const;
};

///////////////////////////////////////////
// Posicionamiento: implementacion
//////////////////////////////////////////

/** Devuelve la posicion absoluta del lado izquierdo del elemento UI */
int Posicionamiento::_obtener_pos_abs_x(const float ancho_forma) const {
    switch (alineamiento) {
        case Align::Left:
            return contenedor.left + posicion_relativa.x;
        case Align::Right:
            {
                // clang-format off
                // Aqui la posicion relativa es desde el lado derecho del padre
                const auto contenedor_derecha = contenedor.left + contenedor.width;
                const auto pos_abs_derecha = contenedor_derecha + posicion_relativa.x;
                return pos_abs_derecha - ancho_forma;
                // clang-format on
            }
        default:
            throw std::out_of_range("Valor no manejado");
    }
}

/**
 * @brief Calcula la posicion absoluta del elemento UI en la ventana.
 *
 * Toma en cuenta el factor de escala y el ancho del elemento para determinar
 * su nueva posicion absoluta en la ventana. Esta posicion se ajusta segun
 * el alineamiento especificado.
 *
 * @param escala Factor de escala que se aplica al tamano del elemento UI.
 * @param ancho_forma Ancho actual del elemento UI.
 * @return Un par de sf::Vector2f que representan la nueva posicion del elemento
 * y su etiqueta ajustada, respectivamente.
 */
std::pair<sf::Vector2f, sf::Vector2f>
Posicionamiento::calcular_posicion_absoluta(
    const double escala, const float ancho_forma
) const {
    const int margen = medidas::MARGEN_BOTON * (escala * escala);
    const auto margen_corregido = margen * 0.7;
    const int x = _obtener_pos_abs_x(ancho_forma);
    const int y = contenedor.getPosition().y + posicion_relativa.y;
    // Ajustamos para evitar un margen excesivo arriba y a la izquierda
    return {
        sf::Vector2f(x, y),
        sf::Vector2f(x + margen_corregido, y + margen_corregido)
    };
}

///////////////////////////////////////////
// BotonConTexto
//////////////////////////////////////////

size_t BotonConTexto::_proximo_id = 1;

//////// Metodos privados

/**
 * @brief Constructor por defecto privado.
 */
BotonConTexto::BotonConTexto() { //
    posicionamiento = std::make_unique<Posicionamiento>();
    _asignar_id();
};

/*
 * Debe ser llamado en todos los constructores para garantizar que ningun boton
 * se queda sin su _id.
 */
void BotonConTexto::_asignar_id() {
    if (!_id.has_value()) {
        _id = _proximo_id++;
    }
}

/**
 * @brief Calcula y establece la posicion absoluta del boton.
 *
 * Esta funcion actualiza la posicion absoluta del boton en la
 * ventana, tomando en cuenta el alineamiento actual y el factor de escala del
 * boton. La posicion absoluta se calcula a partir de la posicion relativa y las
 * dimensiones del rectangulo padre. Esta posicion estara a la derecha o a la
 * izquierda del boton de acuerdo con el alineamiento.
 */
void BotonConTexto::_actualizar_posicion_absoluta() {
    const auto [pos_forma, pos_etiqueta] =
        posicionamiento->calcular_posicion_absoluta(
            _escala, _forma.getGlobalBounds().width
        );

    _forma.setPosition(pos_forma);
    _etiqueta.setPosition(pos_etiqueta);
}

//////// Metodos publicos

/**
 * @brief Constructor que inicializa un boton con texto pero sin posicion
 * definida.
 *
 * La apariencia del boton se escala segun el parametro proporcionado
 *
 * @param boton_data Estructura que contiene los datos del boton como el texto,
 *                   color del texto, y color de fondo.
 * @param font Fuente utilizada para el texto del boton.
 * @param escala Factor de escala para el tamano del boton y del texto.
 */
BotonConTexto::BotonConTexto(
    const BotonDataConFont &boton_data, //
    double escala                       //
)
    : BotonConTexto() {
    this->_escala = escala;
    // La escala del margen es proporcional al cuadrado de la escala del boton
    const int margen = medidas::MARGEN_BOTON * (escala * escala);
    const auto margen_ambos_lados = margen * 2;

    // Primero creamos la etiqueta para usar sus limites en el Rect
    _etiqueta = crearEtiqueta(
        boton_data.data.texto,                  //
        medidas::TAMANO_TEXTO_BOTONES * escala, //
        boton_data.data.color_texto,            //
        boton_data.font                         //
    );
    const sf::FloatRect rect_etiqueta = _etiqueta.getGlobalBounds();

    _forma.setSize(sf::Vector2f(
        rect_etiqueta.width + margen_ambos_lados,
        rect_etiqueta.height + margen_ambos_lados
    ));
    _forma.setFillColor(boton_data.data.color_fondo);
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
    const BotonDataConFont &boton_data, //
    const sf::Vector2f &posicion,       //
    Align align,                        //
    double escala                       //
)
    : BotonConTexto(boton_data, escala) {
    establecer_posicion(posicion, align);
};

BotonConTexto &BotonConTexto::operator=(BotonConTexto &&) noexcept = default;
BotonConTexto::BotonConTexto(BotonConTexto &&otro) noexcept = default;
BotonConTexto::~BotonConTexto() = default;

/**
 * @brief Establece el rectangulo padre y recalcula la posicion absoluta del
 * boton.
 *
 * Esta funcion define el rectangulo padre que se utiliza para calcular la
 * posicion absoluta del boton. Despues de establecer el rectangulo padre,
 * actualiza la posicion del boton.
 *
 * @param rect El rectangulo que representa el espacio disponible para el boton.
 */
void BotonConTexto::establecer_contenedor(const sf::FloatRect &rect) {
    posicionamiento->contenedor = rect;
    _actualizar_posicion_absoluta();
}

/**
 * @brief Establece la posicion relativa del boton y actualiza su posicion
 * absoluta.
 *
 * Define la posicion relativa del boton y su alineamiento. Con estos nuevos
 * valores, actualiza la posicion del boton.
 *
 * @param posicion Nueva posicion relativa del boton.
 * @param align Alineamiento del boton con respecto a su posicion relativa.
 */
void BotonConTexto::establecer_posicion(
    const sf::Vector2f &posicion, //
    const Align align             //
) {
    posicionamiento->alineamiento = align;
    posicionamiento->posicion_relativa = posicion;
    _actualizar_posicion_absoluta();
}

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
/**
 * @brief Actualiza la parte visual del boton.
 *
 *   Verifica si el boton esta marcado como visible antes de proceder.
 * Si el boton esta activo, se muestra con su color activo; de lo contrario,
 * se muestra con un color gris por defecto.
 *   La etiqueta del boton se dibuja sobre el boton.
 */

void BotonConTexto::actualizar() {
    if (!visible)
        return;
    if (!colorBotonActivo.has_value())
        colorBotonActivo = _forma.getFillColor();
    if (_activo) {
        _forma.setFillColor(colorBotonActivo.value());
    } else {
        _forma.setFillColor(sf::Color(100, 100, 100));
    }
}

/**
 * @brief Dibuja el boton en el target de renderizado proporcionado.
 *
 * Esta funcion es responsable de renderizar el boton en el target de
 * renderizado (como la ventana de la aplicacion). Verifica si el boton esta
 * marcado como visible antes de proceder.
 *
 * @param target Referencia al target de renderizado donde se dibujara el
 * boton.
 */
void BotonConTexto::draw(
    sf::RenderTarget &target, //
    sf::RenderStates states   //
) const {
    if (!visible)
        return;
    dibujar_elementos(target, std::make_tuple(_forma, _etiqueta));
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

/**
 * Activo o desactiva el boton en funcion de si se cumple la condicion.
 */
void BotonConTexto::activacion_condicional(bool condicion) {
    if (condicion) {
        activar();
    } else {
        desactivar();
    }
}

/**
 * Devuelve el id del boton
 */
size_t BotonConTexto::get_id() const { //
    assert(_id.has_value());
    return _id.value();
}

/**
 * @brief Verifica si el boton esta actualmente activo.
 *
 * Retorna el estado actual del boton, indicando si este esta activo y puede
 * interactuar con el usuario o no.
 *
 * @return true si el boton esta activo, false en caso contrario.
 */
bool BotonConTexto::esta_activo() const { //
    return _activo;
}
