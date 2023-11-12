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
#include "Menu.h"

class Map;
class Layer;
class TextureManager;
class EntityManager;
class Block;
class Entity;
class HealthBar;
class AnimatedObject;
class Hero;
class Menu;

class Engine
{
private:
	Game_State gameState = Game_State::MENU;
	Menu* menu;
	TextureManager* texture_manager;
	FileManager* file_manager;
	//AnimatedObject anime;
	EntityManager* entity_manager;
	Entity* hero;
	std::vector <Map> levels;
	uint16_t current_level;
	sf::View view;
	uint16_t antogonist = 666;
	void create_entity(std::string entity_texture_path, bool is_playable);
	void init_view();
	void update_view(sf::Vector2f pos);
	bool next_level();
public:
	Engine() = delete;
	Engine(char** argv);
	//Engine(std::string saved_file);
	Engine(const Engine& other) = delete;

	void menu_loop(sf::RenderWindow& window, float& timer);
	Game_State getGameState() const;
	void setGameState(Game_State state);
	
	//void set_focus_on_map(uint16_t id);
	void check_collisions(float& time);
	void game_loop(sf::RenderWindow& window, float& timer);
	void map_loop(sf::RenderWindow& window);

	~Engine();
};
