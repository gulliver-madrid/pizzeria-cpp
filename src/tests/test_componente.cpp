#include "../vista/componente.h"
#include <SFML/Graphics/Font.hpp>
#include <gtest/gtest.h>

TEST(Componente, Existe) {
    class A : public Componente {};
    class B : public Componente {};
    std::shared_ptr<A> a = std::make_shared<A>();
    B b;
    b.add_child(a);
    ASSERT_EQ(1, b.get_children().size());
}

TEST(Componente, ConPosibleFont) {
    class A : public ComponenteConFont {};
    class B : public ComponenteConFont {};
    std::shared_ptr<A> a = std::make_shared<A>();
    B b;
    b.add_child(a);
    ASSERT_EQ(1, b.get_children().size());
}

TEST(Componente, AnadeFont) {
    class A : public ComponenteConFont {};
    class B : public ComponenteConFont {};
    std::shared_ptr<A> a = std::make_shared<A>();
    B b;
    const auto font_ptr = std::make_shared<sf::Font>();
    ASSERT_EQ(false, a->has_font());
    OptionalFont font;
    font.set_pointer(font_ptr);
    b.set_font(font);
    b.add_child(a);
    ASSERT_EQ(1, b.get_children().size());
    ASSERT_EQ(true, a->has_font());
}
