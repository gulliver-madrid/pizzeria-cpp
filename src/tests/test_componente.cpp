#include "../vista/componente.h"
#include <SFML/Graphics/Font.hpp>
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
    ASSERT_EQ(true, a->has_font);
    b.add_child(a);
    ASSERT_EQ(1, b.children.size());
}

TEST(Componente, AnadeFont) {
    class A : public ComponenteConPosibleFont {};
    class B : public ComponenteConPosibleFont {};
    std::shared_ptr<A> a = std::make_shared<A>();
    B b;
    ASSERT_EQ(true, a->has_font);
    const auto font = std::make_shared<sf::Font>();
    ASSERT_EQ(false, a->font.exists());
    b.font.set_pointer(font);
    b.add_child(a);
    ASSERT_EQ(1, b.children.size());
    ASSERT_EQ(true, a->font.exists());
}
