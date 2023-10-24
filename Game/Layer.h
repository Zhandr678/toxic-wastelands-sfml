#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Block.h"

class Layer
{
private:
	std::string name;
	std::vector <std::vector <Block>> layer;
	std::vector <std::vector <bool>> grid;
	uint16_t horizontal_size, vertical_size;
	Texture_Type type;
public:
	friend class Engine;

	Layer(std::string name, std::vector <std::vector <Block>> layer, std::vector <std::vector <bool>> grid, 
		Texture_Type type, uint16_t horizontal_size = MAX_BLOCKS_HORIZONTAL, uint16_t vertical_size = MAX_BLOCKS_VERTICAL);
	Layer(const Layer& other);
	Layer& operator =(const Layer& other);

	void draw_layer(sf::RenderWindow& window) const;
	Texture_Type get_type() const;
	bool intersects_hitbox_grid(float x, float y) const;
	std::pair <uint16_t, uint16_t> get_size() const;

	~Layer();
};

