#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Pizzería");
    window.setFramerateLimit(144);

    // Contador
    int contador = 0;

    // Fuente y Texto para el contador
    sf::Font font;
    if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
        return EXIT_FAILURE;
    }

    sf::Text texto;
    texto.setFont(font);
    texto.setCharacterSize(48);
    texto.setPosition(50, 50);
    texto.setFillColor(sf::Color::White);

    // Botón para incrementar el contador
    sf::RectangleShape boton(sf::Vector2f(100, 50));
    boton.setFillColor(sf::Color::Green);
    boton.setPosition(50, 150);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::FloatRect botonBounds = boton.getGlobalBounds();

                if (botonBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
                {
                    contador++;
                }
            }
        }

        texto.setString("Contador: " + std::to_string(contador));

        window.clear();
        window.draw(texto);
        window.draw(boton);
        window.display();
    }

    return 0;
}
