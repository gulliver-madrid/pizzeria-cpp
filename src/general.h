#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

enum class FaseNivel {
    MostrandoInstrucciones,
    Activa,
    EsperaAntesDeResultado,
    MostrandoResultado,
    Reiniciando,
    Saliendo
};
