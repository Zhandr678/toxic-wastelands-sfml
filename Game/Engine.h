#pragma once
#include <vector> 
#include <nlohmann/json.hpp>
#include <iostream>

#include "TextureManager.h"
#include "EntityManager.h"
#include "Player.h"
#include "Map.h"
#include "Entity.h"
#include "HealthBar.h"
#include "AnimatedObject.h"
#include "Hero.h"
#include "NPC.h";
#include "FileManager.h"

class Map;
class Layer;
class TextureManager;
class EntityManager;
class Block;
class Entity;
class HealthBar;
class AnimatedObject;
class Hero;

class Engine
{
private:
	TextureManager* texture_manager;
	FileManager* file_manager;
	//AnimatedObject anime;
	//EntityManager* entity_manager;
	//Player* player;
	Entity* hero, *enemy;
	std::vector <Map> levels;
	uint16_t current_level;
	//sf::View view;
	//sf::Image gameover;
	void create_map(std::string path, std::string background_path);
	void create_entity(std::string entity_texture_path, bool is_playable);
	//void collision();
public:
	Engine() = delete;
	Engine(char** argv);
	//Engine(std::string saved_file);
	Engine(const Engine& other) = delete;

	//void set_view();
	//void set_focus_on_map(uint16_t id);
	void check_collisions();
	void game_loop(sf::RenderWindow& window, float& timer);
	void map_loop(sf::RenderWindow& window);

	~Engine();
};
