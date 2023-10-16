#include "map.h"

#include <iostream>
#include <map>

int demo_map() { //
    std::cout << std::endl << "Demo map" << std::endl << std::endl;
    // Declara e inicializa un map que mapea strings a enteros
    std::map<std::string, int> edad;

    // Inserta algunos elementos
    edad["Alice"] = 30;
    edad["Bob"] = 40;
    edad["Charlie"] = 50;

    // Accede y muestra el valor usando una clave
    std::cout << std::endl
              << "La edad de Alice es " << edad["Alice"] << std::endl;

    // Itera a través del map
    for (auto &[nombre, edad] : edad) {
        std::cout << nombre << " tiene " << edad << " años." << std::endl;
    }

    return 0;
}
