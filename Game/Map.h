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
private:
	std::vector <Layer> grid;
	sf::Image background_image;
	sf::Texture background_texture;
	sf::Sprite background_sprite;
	float x_left_boundary, x_right_boundary;
	float y_top_boundary, y_bottom_boundary;
public:
	friend class Engine;
	Map(std::vector <Layer> grid, std::string background_file);
	Map(const Map& other);
	Map& operator =(const Map& other);

	sf::Vector2f get_y_boundaries() const;
	sf::Vector2f get_x_boundaries() const;

	bool intersects_with_type(float x, float y, Texture_Type type) const;
	void draw_map(sf::RenderWindow& window);

	~Map() {};
};

