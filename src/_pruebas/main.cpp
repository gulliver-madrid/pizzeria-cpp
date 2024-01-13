#include "class_a.h"
#include <iostream>

struct Class_B {
    int x;
};
void Class_A::f(Class_B b) {}
int main() {
    std::cout << "Esto es una prueba" << std::endl;
    Class_A a;
    Class_B b = {1};
    a.f(b);
    return 0;
}
