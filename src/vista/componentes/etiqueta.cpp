#include "etiqueta.h"
#include "../../shared/font.h"

Etiqueta::Etiqueta(
    const std::string &texto, //
    int tamano_fuente,        //
    const OptionalFont &font  //
) {
    this->font = font;
    etiqueta.setString(texto);
    if (font.exists()) {
        etiqueta.setFont(*font.get_pointer());
        etiqueta.setCharacterSize(tamano_fuente);
    };
}

Etiqueta::Etiqueta(
    const std::string &texto,    //
    int tamano_fuente,           //
    const sf::Color &color,      //
    const OptionalFont &font,    //
    const sf::Vector2f &posicion //
)
    : Etiqueta(texto, tamano_fuente, font) {
    etiqueta.setFillColor(color);
    etiqueta.setPosition(posicion);
}

Etiqueta::Etiqueta(
    const std::string &texto,    //
    const EstiloTexto &estilo,   //
    const OptionalFont &font,    //
    const sf::Vector2f &posicion //
)
    : Etiqueta(texto, estilo.tamano, estilo.color, font, posicion) {}

void Etiqueta::actualizar_texto(const std::string &texto) { //
    etiqueta.setString(texto);
}
sf::FloatRect Etiqueta::get_global_bounds() { //
    return etiqueta.getGlobalBounds();
}
void Etiqueta::set_position(float x, float y) { //
    etiqueta.setPosition(x, y);
}
void Etiqueta::draw(
    sf::RenderTarget &target, //
    sf::RenderStates states   //
) const {
    assert(font.exists());
    target.draw(etiqueta);
};
