#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>

#include "Engine.h"

int main(int argc, char** argv)
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_LENGTH, WINDOW_HEIGHT), "Toxic Wastelands", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);

    Engine engine(argv);
    sf::Clock clock;

    while (window.isOpen())
    {
        engine.map_loop(window);

        sf::Event e;
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        float timer = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        timer /= TIME_SCALING;

        engine.game_loop(window, timer);

        window.display();
    }
}
