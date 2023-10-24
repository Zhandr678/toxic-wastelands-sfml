#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>

#include "Engine.h"

std::string solution_directory(char** argv)
{
	std::string exe_path = std::filesystem::path(argv[0]).parent_path().string();
	exe_path = exe_path.substr(0, exe_path.find_last_of("/\\"));
	exe_path = exe_path.substr(0, exe_path.find_last_of("/\\"));
	return exe_path;
}

int main(int argc, char** argv)
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_LENGTH, WINDOW_HEIGHT), "Toxic Wastelands", sf::Style::Close | sf::Style::Titlebar);

    const std::string solution_dir = solution_directory(argv);
    const std::string maps_dir = solution_dir + "/maps";
    const std::string texture_dir = solution_dir + "/Textures";

    Engine engine(argv, maps_dir);
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
