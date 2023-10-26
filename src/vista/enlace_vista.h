#pragma once

#include <memory>

struct Vista;

/* Debe ser un intermediario entre el modelo y la vista */
struct EnlaceVista {
    // TODO: hacer vista privado
    // TODO: implementar los metodos que faltan

    std::shared_ptr<Vista> vista;

    EnlaceVista(std::shared_ptr<Vista> vista) : vista(vista) {}
    void on_cambio_a_fase_activa() const;
    void on_cambio_a_fase_espera_antes_de_resultado() const;
    void esconder_paneles() const;
};
