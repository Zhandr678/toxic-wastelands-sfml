#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>

#include "Entity.h"
#include "Block.h"
#include "Map.h"
#include "EntityManager.h"
#include "Constants.h"
#include "TextureManager.h"

std::vector <Map> levels;
uint8_t cur_lvl = 0;

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

	TextureManager texture_manager(argv);

	const std::string solution_dir = solution_directory(argv);
	const std::string maps_dir = solution_dir + "/maps";

	levels.push_back(texture_manager.generate_map(maps_dir + "/map1.json", "C:/Users/Home/source/repos/Game/Textures/Map_Textures/Background/background.png"));

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

		levels[cur_lvl].draw_map(window);
		window.display();
	}
}

//int main(int argc, char** argv)
//{
//	sf::RenderWindow window(sf::VideoMode(WINDOW_LENGTH, WINDOW_HEIGHT), "The Game", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);
//	sf::Clock clock;
//
//	TextureManager texture_manager(argv);
//
//	const std::string solution_dir = solution_directory(argv);
//	const std::string maps_dir = solution_dir + "/maps";
//
//	Layer layer({
//		Block(1, "C:/Users/Home/source/repos/Game/Textures/Map_Textures/Tiles/1.png", 32, 32), 
//		Block(2, "C:/Users/Home/source/repos/Game/Textures/Map_Textures/Tiles/2.png", 0, 32),
//		Block(1, "C:/Users/Home/source/repos/Game/Textures/Map_Textures/Tiles/1.png", 64, 64),
//	}, true);
//
//	Map m({layer}, "C:/Users/Home/source/repos/Game/Textures/Map_Textures/Background/background.png");
//
//	while (window.isOpen())
//	{
//		float timer = clock.getElapsedTime().asMicroseconds();
//		clock.restart();
//		timer /= TIME_SCALING;
//
//		sf::Event e;
//		while (window.pollEvent(e))
//		{
//			if (e.type == e.Closed) { window.close(); }
//		}
//
//		m.draw_map(window);
//		window.display();
//	}
//}