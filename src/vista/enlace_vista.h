#pragma once

#include <memory>

struct Estado;
struct Vista;
namespace sf {
    class RenderWindow;
}

/* Debe ser un intermediario entre el modelo y la vista */
class EnlaceVista {
    // TODO: hacer vista privado
    // TODO: implementar los metodos que faltan

  public:
    std::shared_ptr<Vista> vista;
    EnlaceVista(std::shared_ptr<Vista> vista) : vista(vista) {}
    void on_cambio_a_fase_activa() const;
    void on_cambio_a_fase_espera_antes_de_resultado() const;
    void esconder_paneles() const;
    void actualizarIU(
        sf::RenderWindow &ventana, //
        const Estado &estado       //
    ) const;
};