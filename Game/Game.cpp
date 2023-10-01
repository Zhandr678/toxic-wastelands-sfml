#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Entity.h"
#include "Block.h"
#include "Map.h"
#include "EntityManager.h"
#include "Constants.h"

#include <nlohmann/json.hpp>

using namespace nlohmann;

std::vector <Map> levels;
std::string solution_dir, texture_dir, map_texture_dir;

std::string solution_directory(char** argv)
{
	std::string exe_path = std::filesystem::path(argv[0]).parent_path().string();
	exe_path = exe_path.substr(0, exe_path.find_last_of("/\\"));
	exe_path = exe_path.substr(0, exe_path.find_last_of("/\\"));
	return exe_path;
}

int main(int argc, char **argv)
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_LENGTH, WINDOW_HEIGHT), "The Game", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);
	sf::Clock clock;

	json j{};
	j["age"] = 4;
	j.

	while (window.isOpen())
	{
		float timer = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		timer /= TIME_SCALING;
		
		sf::Event e;
		while (window.pollEvent(e))
		{
			if (e.type == e.Closed) { window.close(); }
		}

		window.display();
	}
}