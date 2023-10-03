#include "Map.h"

Map::Map(std::vector<Layer> grid, std::string background_file) : grid(grid)
{
	this->background_image.loadFromFile(background_file);
	this->background_texture.loadFromImage(this->background_image);
	this->background_sprite.setTexture(this->background_texture);
	this->background_sprite.setPosition(0.0f, 0.0f);
}

Map::Map(const Map& other)
{
	this->grid = other.grid;
	this->background_image = other.background_image;
	this->background_texture.loadFromImage(this->background_image);
	this->background_sprite.setTexture(this->background_texture);
	this->background_sprite.setPosition(0.0f, 0.0f);
}

Map& Map::operator=(const Map& other)
{
	if (this != &other)
	{
		this->background_image = other.background_image;
		this->background_texture.loadFromImage(this->background_image);
		this->background_sprite.setTexture(this->background_texture);
		this->background_sprite.setPosition(0, 0);
	}
	return *this;
}

void Map::draw_map(sf::RenderWindow& window)
{
	window.draw(this->background_sprite);
	for (const Layer& layer : this->grid)
	{
		layer.draw_layer(window);
	}
}

void Map::update_block(float x, float y, sf::String new_block)
{
}

void Map::update_block(int x, int y, sf::String new_block)
{
}
