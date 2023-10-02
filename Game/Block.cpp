#include "Block.h"

Block::Block(uint16_t id, std::string file, float x, float y)
{
	this->id = id;
	this->file = file;
	this->image.loadFromFile(this->file);
	this->texture.loadFromImage(this->image);
	this->length = this->image.getSize().x;
	this->width = this->image.getSize().y;
	this->x = x; this->y = y;
}

void Block::create_mask_from_color(sf::Color color)
{
	this->image.createMaskFromColor(color);
	this->texture.loadFromImage(this->image);
}

void Block::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}
