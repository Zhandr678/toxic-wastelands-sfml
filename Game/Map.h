#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

#include "Constants.h"
#include "Block.h"
#include "Layer.h"

class Map
{
private:
	std::vector <Layer> grid;
	sf::Image background_image;
	sf::Texture background_texture;
	sf::Sprite background_sprite;
public:
	Map(std::vector <Layer> grid, std::string background_file);
	Map(const Map& other);
	Map& operator =(const Map& other);

	void draw_map(sf::RenderWindow& window);
	void update_block(float x, float y, sf::String new_block);
	void update_block(int x, int y, sf::String new_block);

	~Map() {};
};

