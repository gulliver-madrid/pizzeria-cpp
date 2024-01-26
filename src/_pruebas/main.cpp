#include "class_a.h"
#include <iostream>

class Class_B {
  public:
    int x;
};
void Class_A::f(Class_B) {}
int main() {
    std::cout << "Esto es una prueba" << std::endl;
    Class_A a;
    Class_B b_instance = {1};
    a.f(b_instance);
    return 0;
}
