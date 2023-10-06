#pragma once
#include <vector> 
#include <nlohmann/json.hpp>
#include <iostream>

#include "TextureManager.h"
#include "EntityManager.h"
#include "Player.h"
#include "Map.h"


class Map;
class Layer;
class TextureManager;
class EntityManager;
class Block;
class Player;

class Engine
{
private:
	TextureManager* texture_manager;
	EntityManager* entity_manager;
	Player* player;
	std::vector <Map> levels;
	uint16_t current_level;
	void create_map(std::string path, std::string background_path);
	void create_entity(std::string entity_texture_path, bool is_playable);
	void collision();
public:
	Engine() = delete;
	Engine(char** argv, std::string maps_folder_path);
	//Engine(std::string saved_file);
	Engine(const Engine& other) = delete;
	
	void set_view_on(uint16_t id);
	void set_focus_on_map(uint16_t id);
	void loop(sf::RenderWindow& window, float& timer);

	~Engine();
};
