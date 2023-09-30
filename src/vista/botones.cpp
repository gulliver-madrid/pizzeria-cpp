#include "botones.h"
#include "../modelo/dominio.h"
#include "vista_basics.h"
#include <cassert>

namespace medidas {
    constexpr int MARGEN_BOTON = 20;
    constexpr int TAMANO_TEXTO_BOTONES = 32;
} // namespace medidas

/* Crea un botón rectangular con texto */
BotonConTexto crearBotonConTexto(
    const std::string &texto, const sf::Color &color_fondo,
    const sf::Vector2i &posicion, const sf::Font &font,
    const sf::Color &color_texto, float escala
) {
    int x = posicion.x;
    int y = posicion.y;
    // La escala del margen es proporcional al cuadrado de la escala del botón
    int margen = medidas::MARGEN_BOTON * (escala * escala);
    // Primero creamos la etiqueta para usar sus límites en el Rect
    sf::Text etiqueta = crearEtiqueta(
        medidas::TAMANO_TEXTO_BOTONES * escala, font, color_texto
    );
    etiqueta.setString(texto);
    // Ajustamos para evitar un margen excesivo arriba y a la izquierda
    etiqueta.setPosition(x + margen * 0.7, y + margen * 0.7);
    sf::FloatRect textRect = etiqueta.getGlobalBounds();

    // Rect
    sf::RectangleShape rect(
        sf::Vector2f(textRect.width + margen * 2, textRect.height + margen * 2)
    );
    rect.setFillColor(color_fondo);
    rect.setPosition(x, y);

    return BotonConTexto(rect, etiqueta);
};

Botones::Botones(sf::Font &font) {
    empezar = crearBotonConTexto(
        "Empezar", sf::Color::Green, sf::Vector2i(500, 450), font,
        sf::Color::Black
    );
    int i = 0;
    for (auto tp : tipos_de_pizza) {
        encargar[tp] = crearBotonConTexto(
            tipo_pizza_to_string[tp], sf::Color::Green,
            sf::Vector2i(
                obtener_posicion_x_panel(IndicePanel::PANEL_ENCARGAR) +
                    medidas::MARGEN_IZQ_ETIQUETAS,
                medidas::FILA_CONTENIDO_PANEL + 80 * i
            ),
            font, sf::Color::Black
        );
        i++;
    }
    i = 0;
    for (auto tp : tipos_de_pizza) {
        despachar[tp] = crearBotonConTexto(
            "Despachar", sf::Color::Green,
            sf::Vector2i(
                obtener_posicion_x_panel(IndicePanel::PANEL_PREPARADAS) +
                    medidas::MARGEN_IZQ_ETIQUETAS +
                    (medidas::ANCHO_PANEL * 0.55),
                medidas::FILA_CONTENIDO_PANEL + 50 * i
            ),
            font, sf::Color::Black, 0.7
        );
        i++;
    }

    reiniciar = crearBotonConTexto(
        "Reiniciar", sf::Color::Blue,
        sf::Vector2i(1440, medidas::FILA_BOTONES_GENERALES), font
    );
    salir = crearBotonConTexto(
        "Salir", sf::Color::Red,
        sf::Vector2i(1640, medidas::FILA_BOTONES_GENERALES), font
    );

    todos = {&empezar, &reiniciar, &salir};
    for (auto &par : despachar) {
        todos.push_back(&par.second);
    }
    for (auto &par : encargar) {
        todos.push_back(&par.second);
    }
    assert(todos.size() == 3 + NUMERO_DE_TIPOS_DE_PIZZA * 2);
}

void Botones::dibujar(sf::RenderWindow &ventana) const {
    for (auto boton_ptr : todos) {
        assert(boton_ptr != nullptr);
        boton_ptr->dibujar(ventana);
    }
}

void Botones::mostrar_botones_nivel(bool nuevo_valor) {
    for (auto tp : tipos_de_pizza) {
        despachar[tp].visible = nuevo_valor;
        encargar[tp].visible = nuevo_valor;
    }
}
