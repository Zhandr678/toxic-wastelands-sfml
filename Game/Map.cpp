#include "Map.h"

Map::Map(std::vector<sf::String> background_files, std::vector<std::vector<sf::String>> block_files)
{
	this->background_image.create(WINDOW_LENGTH, WINDOW_HEIGHT);
	for (const sf::String& file : background_files)
	{
		sf::Image i;
		i.loadFromFile(file);
		this->background_image.copy(i, 0, 0);
	}
	this->background_texture.loadFromImage(this->background_image);
	this->background_sprite.setTexture(this->background_texture);

	for (int i = 0; i < block_files.size(); i++)
	{
		std::vector <Block> temp;
		for (int j = 0; j < block_files[i].size(); j++)
		{
			if (block_files[i][j] != NULL_FILE)
			{
				temp.push_back(Block(block_files[i][j], i * TILE_SIZE, j * TILE_SIZE));
			}
		}
		this->grid.push_back(temp);
	}
}

void Map::draw(sf::RenderWindow& window)
{
	window.draw(this->background_sprite);

	for (auto& vec : this->grid)
	{
		for (Block& block : vec)
		{
			block.draw(window);
		}
	}
}

void Map::update_block(float x, float y, sf::String new_block)
{
}

void Map::update_block(int x, int y, sf::String new_block)
{
}
