#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include <map>

#include "Constants.h"
#include "Block.h"
#include "Layer.h"

class Map
{
public:
	std::vector <Layer> grid;
	sf::Image background_image;
	sf::Texture background_texture;
	sf::Sprite background_sprite;
public:
	friend class Engine;
	Map(std::vector <Layer> grid, std::string background_file);
	Map(const Map& other);
	Map& operator =(const Map& other);

	bool intersects_with_type(float x, float y, Texture_Type type);
	void draw_map(sf::RenderWindow& window);

	~Map() {};
};

