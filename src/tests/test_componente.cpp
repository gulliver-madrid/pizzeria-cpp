#include "../vista/componentes/componente.h"
#include <SFML/Graphics/Font.hpp>
#include <gtest/gtest.h>

template <typename C> class ComponenteGenericoTest : public testing::Test {
  protected:
    class ComponenteConcreto : public C {
        virtual void draw(sf::RenderTarget &, sf::RenderStates) const override {
        }
    };
    class B : public ComponenteConcreto {};
    class A : public ComponenteConcreto {};
};

using ComponenteTest = ComponenteGenericoTest<Componente>;
using ComponenteConFontTest = ComponenteGenericoTest<ComponenteConFont>;

TEST_F(ComponenteTest, AnadeHijo) {
    std::shared_ptr<B> b = std::make_shared<B>();
    A a;
    a.add_child(b);
    ASSERT_EQ(1, a.get_children().size());
}

TEST_F(ComponenteConFontTest, AnadeHijoConPosibleFont) {
    std::shared_ptr<B> b = std::make_shared<B>();
    A a;
    a.add_child(b);
    ASSERT_EQ(1, a.get_children().size());
}

TEST_F(ComponenteConFontTest, AnadeFont) {
    // Chequea que al anadir un hijo a un componente con la fuente
    // establecida, esta se pasa tambien al hijo
    std::shared_ptr<B> b = std::make_shared<B>();
    A a;
    const auto font_ptr = std::make_shared<sf::Font>();
    ASSERT_EQ(false, b->has_font());
    OptionalFont font;
    font.set_pointer(font_ptr);
    a.set_font(font);
    a.add_child(b);
    ASSERT_EQ(true, b->has_font());
}
