#include "debug_sfml.h"

namespace debug {
    void debug_rect(sf::RectangleShape &rect, std::string name) {
        using namespace std;
        cout << name << ".getPosition(): " << rect.getPosition().x << ", "
             << rect.getPosition().y << endl;
        cout << name << ".getLocalBounds(): " << rect.getLocalBounds().left
             << ", " << rect.getLocalBounds().top << endl;
        cout << name << ".getGlobalBounds(): " << rect.getGlobalBounds().left
             << ", " << rect.getGlobalBounds().top << ", "
             << rect.getGlobalBounds().width << ", "
             << rect.getGlobalBounds().height << endl;
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
} // namespace debug
