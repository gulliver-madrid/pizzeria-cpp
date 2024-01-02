#include "prueba.h"
#include "../modelo/dominio.h"
#include "../modelo/modelo.h"
#include <iostream>

int demo_prueba() {
    using namespace modelo;
    using namespace dominio;
    try {
        std::map<TipoPizza, PedidoTipoPizza> contenido(
            {{TipoPizza::Margarita, {2, 5}}, {TipoPizza::Pepperoni, {1, 4}}}
        );

        const auto e = contenido.at(TipoPizza::CuatroQuesos);
    } catch (const std::out_of_range &e) {
        std::cout << "Capturada excepcion out_of_range: " << e.what()
                  << std::endl;
        throw;
    } catch (const std::exception &e) {
        std::cout << "Capturada otra excepcion: " << e.what() << std::endl;
        return 2;
    }

    std::cout << "Ninguna excepcion capturada." << std::endl;
    return 0;
    // Pedido pedido(std::move(contenido));
    // auto c = contenido;
    // std::cout << 111 << std::endl;
    // c.clear();
    // std::cout << 222 << std::endl;
    // const auto d = c.at(TipoPizza::Margarita);
    // std::cout << 333 << std::endl;
    // std::cout << c.empty() << std::endl;
    // std::cout << c.size() << std::endl;
    return 0;
}
