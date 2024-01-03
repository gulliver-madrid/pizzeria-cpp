#pragma once

#include "realizador_base.h"

struct Estado;
enum class FaseNivel;

class Realizador : public RealizadorBase {

  private:
    Estado &estado;

  public:
    Realizador(Estado &estado);

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
