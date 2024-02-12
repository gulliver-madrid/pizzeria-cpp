#include "debug_sfml.h"
#include <SFML/Graphics/RectangleShape.hpp>

namespace debug {
    void debug_rect(sf::RectangleShape &rect, std::string name) {
        using namespace std;
        cout << name << ".getPosition(): " << rect.getPosition().x << ", "
             << rect.getPosition().y << endl;
        cout << name << ".getLocalBounds(): " << rect.getLocalBounds().left
             << ", " << rect.getLocalBounds().top << endl;
        cout << rect_to_string(
                    rect.getGlobalBounds(), name + ".getGlobalBounds()"
                )
             << endl;
    }

    void debug_float_rect(sf::FloatRect rect) {
        using namespace std;
        cout << "getPosition(): " << rect.getPosition().x << ", "
             << rect.getPosition().y << endl;
        cout << "left: " << rect.left << endl;
        cout << "top: " << rect.top << endl;
        cout << "width: " << rect.width << endl;
        cout << "height: " << rect.height << endl;
        cout << endl;
    }

    std::string rect_to_string(const sf::FloatRect &rect, std::string name) {
        return name + ": left " + std::to_string(rect.left) + ", top " +
               std::to_string(rect.top) + ", width " +
               std::to_string(rect.width) + ", height" +
               std::to_string(rect.height);
    }
} // namespace debug
