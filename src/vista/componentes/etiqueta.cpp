#include "etiqueta.h"
#include "../../juego_assert.h"
#include "../../shared/font.h"

Etiqueta::Etiqueta(
    const std::string &texto, //
    int tamano_fuente,        //
    const std::string nombre  //
) {
    this->font = font;
    etiqueta.setString(texto);
    etiqueta.setCharacterSize(tamano_fuente);
    this->nombre = nombre;
}

Etiqueta::Etiqueta(
    const std::string &texto,     //
    int tamano_fuente,            //
    const sf::Color &color,       //
    const sf::Vector2f &posicion, //
    const std::string nombre      //
)
    : Etiqueta(texto, tamano_fuente, nombre) {
    etiqueta.setFillColor(color);
    etiqueta.setPosition(posicion);
}

Etiqueta::Etiqueta(
    const std::string &texto,     //
    const EstiloTexto &estilo,    //
    const sf::Vector2f &posicion, //
    const std::string nombre      //
)
    : Etiqueta(texto, estilo.tamano, estilo.color, posicion, nombre) {}

void Etiqueta::actualizar_texto(const std::string &texto) { //
    etiqueta.setString(texto);
}
sf::FloatRect Etiqueta::get_global_bounds() { //
    return etiqueta.getGlobalBounds();
}
void Etiqueta::set_position(float x, float y) { //
    etiqueta.setPosition(x, y);
}
void Etiqueta::set_font(const OptionalFont &new_font) {
    ComponenteConFont::set_font(new_font);
    etiqueta.setFont(*new_font.get_pointer());
}
void Etiqueta::set_color(const sf::Color &color) {
    etiqueta.setFillColor(color);
}
void Etiqueta::draw(
    sf::RenderTarget &target, //
    sf::RenderStates          //
) const {
    juego_assert(font.exists(), "Falta la fuente en " + nombre);
    target.draw(etiqueta);
};
