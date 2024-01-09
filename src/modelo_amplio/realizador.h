#pragma once

#include "realizador_base.h"

struct ModeloAmplio;
enum class FaseNivel;

class Realizador : public RealizadorBase {

  private:
    ModeloAmplio &modelo_amplio;

  public:
    Realizador(ModeloAmplio &modelo_amplio);

    /* Encarga una pizza a la cocina del tipo indicado */
    NuevaFase encargar_pizza( //
        const dominio::TipoPizza tp
    );

    /*
     * Despacha una pizza a los clientes del tipo indicado. Devuelve la nueva
     * fase si corresponde.
     */
    NuevaFase despachar_pizza( //
        const dominio::TipoPizza tp
    );

    NuevaFase alternar_grid();
    NuevaFase empezar();
};
