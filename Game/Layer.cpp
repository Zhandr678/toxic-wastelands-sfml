#include "Layer.h"

Layer::Layer(std::string name, std::vector<std::vector <Block>> layer, std::vector <std::vector <bool>> grid, 
	Texture_Type type, uint16_t horizontal_size, uint16_t vertical_size) :
	name(name), layer(layer), grid(grid), type(type), horizontal_size(horizontal_size), vertical_size(vertical_size)
{
}

Layer::Layer(const Layer& other) :
	name(other.name), layer(other.layer), grid(other.grid), type(other.type), horizontal_size(other.horizontal_size), vertical_size(other.vertical_size)
{
}

Layer& Layer::operator=(const Layer& other)
{
	if (this != &other)
	{
		this->layer = other.layer;
		this->grid = other.grid;
		this->name = other.name;
		this->type = other.type;
		this->horizontal_size = other.horizontal_size;
		this->vertical_size = other.vertical_size;
	}
	return *this;
}

void Layer::draw_layer(sf::RenderWindow& window) const
{
	for (int i = 0; i < this->vertical_size; i++)
	{
		for (int j = 0; j < this->horizontal_size; j++)
		{
			this->layer[i][j].draw(window);
		}
	}
}

Texture_Type Layer::get_type() const
{
	return this->type;
}

bool Layer::intersects_hitbox_grid(float x, float y) const
{
	int index_y = y / TILE_SIZE, index_x = x / TILE_SIZE;
	return this->grid[index_y + 1][index_x];
}

Layer::~Layer() {}