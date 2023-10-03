#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Block.h"

class Layer 
{
private:
	bool is_collidable;
	std::vector <Block> layer;
public:
	Layer(std::vector <Block> layer, bool is_collidable);
	Layer(const Layer& other);
	Layer& operator =(const Layer& other);

	void draw_layer(sf::RenderWindow& window) const;

	~Layer();
};

