#include "../tiempo.h"
#include <iostream>

using namespace std;

int min_example() {
    // Comprobacion de los metodos de comparacion de Tiempo
    auto t1 = sf::seconds(1);
    auto t2 = sf::seconds(2);
    std::cout << "(t1 < t2) " << (t1 < t2) << std::endl;
    std::cout << "(t1 > t2) " << (t1 > t2) << std::endl;
    std::cout << "(t1 == t2) " << (t1 == t2) << std::endl;
    std::cout << "(t1 <= t2) " << (t1 <= t2) << std::endl;
    std::cout << "(t1 >= t2) " << (t1 >= t2) << std::endl;
    return 0;
}
