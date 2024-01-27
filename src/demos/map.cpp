#include "map.h"

#include <iostream>
#include <map>

int demo_map() { //
    std::cout << std::endl << "Demo map" << std::endl << std::endl;
    // Declara e inicializa un map que mapea strings a enteros
    std::map<std::string, int> edades;

    // Inserta algunos elementos
    edades["Alice"] = 30;
    edades["Bob"] = 40;
    edades["Charlie"] = 50;

    // Accede y muestra el valor usando una clave
    std::cout << std::endl
              << "La edad de Alice es " << edades["Alice"] << std::endl;

    // Itera a traves del map
    for (auto &[nombre, edad] : edades) {
        std::cout << nombre << " tiene " << edad << " años." << std::endl;
    }

    return 0;
}
