#include "Layer.h"

Layer::Layer(std::vector<Block> layer, bool is_collidable)
{
	this->layer = layer;
	this->is_collidable = is_collidable;
}

Layer::Layer(const Layer& other)
{
	this->layer = other.layer;
	this->is_collidable = other.is_collidable;
}

Layer& Layer::operator=(const Layer& other)
{
	if (this != &other)
	{
		this->layer = other.layer;
		this->is_collidable = other.is_collidable;
	}
	return *this;
}

void Layer::draw_layer(sf::RenderWindow& window) const
{
	for (const Block& block : this->layer)
	{
		block.draw(window);
	}
}

Layer::~Layer() {}

