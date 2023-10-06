#include "Map.h"

Map::Map(std::vector<Layer> grid, std::string background_file)
{
	this->background_image.loadFromFile(background_file);
	this->background_texture.loadFromImage(this->background_image);
	this->background_sprite.setTexture(this->background_texture);
	this->background_sprite.setPosition(0.0f, 0.0f);

	this->grid = grid;
	for (const Layer& layer : grid)
	{
		if (layer.collidable()) {
			auto _layer = layer.get_layer();
			for (const Block& block : _layer)
			{
				block_at[{ block.get_hitbox().left, block.get_hitbox().top }] = true;
			}
		}
	}
}

Map::Map(const Map& other)
{
	this->grid = other.grid;
	this->background_image = other.background_image;
	this->background_texture.loadFromImage(this->background_image);
	this->background_sprite.setTexture(this->background_texture);
	this->background_sprite.setPosition(0.0f, 0.0f);
	for (const Layer& layer : grid)
	{
		if (layer.collidable()) {
			auto _layer = layer.get_layer();
			for (const Block& block : _layer)
			{
				block_at[{ block.get_hitbox().left, block.get_hitbox().top }] = true;
			}
		}
	}
}

Map& Map::operator=(const Map& other)
{
	if (this != &other)
	{
		this->background_image = other.background_image;
		this->background_texture.loadFromImage(this->background_image);
		this->background_sprite.setTexture(this->background_texture);
		this->background_sprite.setPosition(0, 0);
		for (const Layer& layer : grid)
		{
			if (layer.collidable()) {
				auto _layer = layer.get_layer();
				for (const Block& block : _layer)
				{
					block_at[{ block.get_hitbox().left, block.get_hitbox().top }] = true;
				}
			}
		}
	}
	return *this;
}

bool Map::get_block_at(int x, int y)
{
	return block_at[ {x, y} ];
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

std::vector<Layer> Map::get_grid() const
{
	return this->grid;
}
