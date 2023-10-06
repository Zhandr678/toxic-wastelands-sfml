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
	friend class Engine;
	Layer(std::vector <Block> layer, bool is_collidable);
	Layer(const Layer& other);
	Layer& operator =(const Layer& other);

	bool collidable() const;
	Block get_block(uint16_t id) const;
	void draw_layer(sf::RenderWindow& window) const;
	std::vector <Block> get_layer() const;

	~Layer();
};

