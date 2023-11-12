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

        if (engine.getGameState() == Game_State::MENU || engine.getGameState() == Game_State::DEATH || engine.getGameState() == Game_State::FINISH)
        {
            window.clear();
            engine.menu_loop(window, timer);

        }
        else if (engine.getGameState() == Game_State::GAME)
        {
            window.clear();
            engine.map_loop(window);
            engine.game_loop(window, timer);
        }

        window.display();
    }
}
