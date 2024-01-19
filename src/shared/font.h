#pragma once

#include <memory>

namespace sf {
    class Font;
}

///////////////////////////////////////////
// OptionalFont
//////////////////////////////////////////

class OptionalFont {
  private:
    std::shared_ptr<sf::Font> font_ptr;

  public:
    void set_pointer(std::shared_ptr<sf::Font> ptr);
    std::shared_ptr<sf::Font> get_pointer() const;
    bool exists() const;
};

///////////////////////////////////////////
// ObjetoConFont
//////////////////////////////////////////

class ObjetoConFont {
  protected:
    OptionalFont font;

  public:
    ObjetoConFont();
    ObjetoConFont(const OptionalFont &font);
    virtual void set_font(const OptionalFont &new_font);
    virtual bool has_font();
};
