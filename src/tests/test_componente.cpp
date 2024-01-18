#include "../vista/componente.h"
#include <gtest/gtest.h>

TEST(Componente, Existe) {
    class A : public Componente {};
    class B : public Componente {};
    std::shared_ptr<A> a = std::make_shared<A>();
    B b;
    b.add_child(a);
    ASSERT_EQ(false, a->has_font);
}

TEST(Componente, ConPosibleFont) {
    class A : public ComponenteConPosibleFont {};
    class B : public ComponenteConPosibleFont {};
    std::shared_ptr<A> a = std::make_shared<A>();
    B b;
    b.add_child(a);
    ASSERT_EQ(true, a->has_font);
}
