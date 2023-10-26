#pragma once

struct Vista;

/* Debe ser un intermediario entre el modelo y la vista */
struct EnlaceVista {
    // TODO: hacer vista privado
    // TODO: implementar metodos

    std::shared_ptr<Vista> vista;

    EnlaceVista(std::shared_ptr<Vista> vista) : vista(vista) {}
};
