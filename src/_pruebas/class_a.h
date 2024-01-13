#pragma once

#include <iostream>

class Class_B;

class Class_A {
  public:
    Class_A() { std::cout << "Construyendo Class_A" << std::endl; }
    void f(Class_B b);
};
