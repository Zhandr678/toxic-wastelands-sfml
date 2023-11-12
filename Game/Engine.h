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
	AnimatedObject anime;
	EntityManager* entity_manager;
	Entity* hero;
	std::vector <Map> levels;
	uint16_t current_level;
	sf::View view;
	void create_entity(std::string entity_texture_path, bool is_playable);
	void init_view();
	void update_view(sf::Vector2f pos);
	bool next_level();
public:
	Engine() = delete;
	Engine(char** argv);
	//Engine(std::string saved_file);
	Engine(const Engine& other) = delete;

	
	//void set_focus_on_map(uint16_t id);
	void check_collisions(float& time);
	void game_loop(sf::RenderWindow& window, float& timer);
	void map_loop(sf::RenderWindow& window);

	~Engine();
};
