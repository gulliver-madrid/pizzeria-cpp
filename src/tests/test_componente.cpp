#include "../vista/componente.h"
#include <SFML/Graphics/Font.hpp>
#include <gtest/gtest.h>

TEST(Componente, AnadeHijo) {
    class ComponenteConcreto : public Componente {
        virtual void draw(
            sf::RenderTarget &target, //
            sf::RenderStates states   //
        ) const override {}
    };
    class B : public ComponenteConcreto {};
    class A : public ComponenteConcreto {};
    std::shared_ptr<B> b = std::make_shared<B>();
    A a;
    a.add_child(b);
    ASSERT_EQ(1, a.get_children().size());
}

TEST(Componente, AnadeHijoConPosibleFont) {
    class ComponenteConFontConcreto : public ComponenteConFont {
        virtual void draw(
            sf::RenderTarget &target, //
            sf::RenderStates states   //
        ) const override {}
    };
    class B : public ComponenteConFontConcreto {};
    class A : public ComponenteConFontConcreto {};
    std::shared_ptr<B> b = std::make_shared<B>();
    A a;
    a.add_child(b);
    ASSERT_EQ(1, a.get_children().size());
}

TEST(Componente, AnadeFont) {
    class ComponenteConFontConcreto : public ComponenteConFont {
        virtual void draw(
            sf::RenderTarget &target, //
            sf::RenderStates states   //
        ) const override {}
    };
    class B : public ComponenteConFontConcreto {};
    class A : public ComponenteConFontConcreto {};
    std::shared_ptr<B> b = std::make_shared<B>();
    A a;
    const auto font_ptr = std::make_shared<sf::Font>();
    ASSERT_EQ(false, b->has_font());
    OptionalFont font;
    font.set_pointer(font_ptr);
    a.set_font(font);
    a.add_child(b);
    ASSERT_EQ(1, a.get_children().size());
    ASSERT_EQ(true, b->has_font());
}
