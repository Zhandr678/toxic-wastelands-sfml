#include "Block.h"

Block::Block(uint16_t id, std::string file, float x, float y)
{
	this->id = id;
	this->file = file;
	if (file != NULL_FILE) 
	{
		this->image.loadFromFile(this->file);
		this->texture.loadFromImage(this->image);
		this->width = this->image.getSize().x;
		this->height = this->image.getSize().y;
		this->x = x; this->y = y;
		this->sprite.setTexture(this->texture);
		this->sprite.setOrigin(0, this->sprite.getLocalBounds().height);
		this->sprite.setPosition(this->x, this->y);
		this->hitbox = sf::FloatRect(this->x, this->y, TILE_SIZE, TILE_SIZE);
	}
}

Block::Block(const Block& other)
{
	this->id = other.id;
	this->file = other.file;
	if (other.file != NULL_FILE) {
		this->image.loadFromFile(this->file);
		this->texture.loadFromImage(this->image);
		this->height = this->image.getSize().y;
		this->width = this->image.getSize().x;
		this->x = other.x; this->y = other.y;
		this->sprite.setTexture(this->texture);
		this->sprite.setOrigin(0, this->sprite.getLocalBounds().height);
		this->sprite.setPosition(this->x, this->y);
		this->hitbox = other.hitbox;
	}
}

Block& Block::operator=(const Block& other)
{
	if (this != &other) 
	{
		this->id = other.id;
		this->file = other.file;
		if (other.file != NULL_FILE) {
			this->image.loadFromFile(this->file);
			this->texture.loadFromImage(this->image);
			this->height = this->image.getSize().y;
			this->width = this->image.getSize().x;
			this->x = other.x; this->y = other.y;
			this->sprite.setTexture(this->texture);
			this->sprite.setOrigin(0, this->sprite.getLocalBounds().height);
			this->sprite.setPosition(this->x, this->y);
			this->hitbox = other.hitbox;
		}
	}
	return *this;
}

uint16_t Block::get_id() const
{
	return id;
}

void Block::create_mask_from_color(sf::Color color)
{
	this->image.createMaskFromColor(color);
	this->texture.loadFromImage(this->image);
	this->sprite.setTexture(this->texture);
	this->sprite.setPosition(this->x, this->y);
}

void Block::draw(sf::RenderWindow& window) const
{
	window.draw(sprite);
}

sf::FloatRect Block::get_hitbox() const
{
	return this->hitbox;
}

bool Block::contains(float x, float y) const
{
	return this->hitbox.contains(x, y);
}

std::pair<float, float> Block::get_pos() const
{
	return { x, y };
}

Block __NULL_BLOCK__()
{
	Block null(0, NULL_FILE, 0, 0);
	null.is_null = true;
	return null;
}
