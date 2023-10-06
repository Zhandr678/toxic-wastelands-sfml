#include "Block.h"

Block::Block()
{
	
}

Block::Block(uint16_t id, std::string file, float x, float y, bool is_collidable)
{
	this->id = id;
	this->file = file;
	this->image.loadFromFile(this->file);
	this->texture.loadFromImage(this->image);
	this->width = this->image.getSize().x;
	this->height = this->image.getSize().y;
	this->x = x; this->y = y;
	this->sprite.setTexture(this->texture);
	this->sprite.setOrigin(0, this->sprite.getLocalBounds().height);
	this->sprite.setPosition(this->x, this->y);
	this->is_collidable = is_collidable;
	this->hitbox = sf::FloatRect(this->x, this->y, TILE_SIZE, TILE_SIZE);
}

Block::Block(const Block& other)
{
	this->id = other.id;
	this->file = other.file;
	this->image.loadFromFile(this->file);
	this->texture.loadFromImage(this->image);
	this->height = this->image.getSize().y;
	this->width = this->image.getSize().x;
	this->x = other.x; this->y = other.y;
	this->sprite.setTexture(this->texture);
	this->sprite.setOrigin(0, this->sprite.getLocalBounds().height);
	this->sprite.setPosition(this->x, this->y);
	this->is_collidable = other.is_collidable;
	this->hitbox = other.hitbox;
}

Block& Block::operator=(const Block& other)
{
	if (this != &other) 
	{
		this->id = other.id;
		this->file = other.file;
		this->image.loadFromFile(this->file);
		this->texture.loadFromImage(this->image);
		this->height = this->image.getSize().y;
		this->width = this->image.getSize().x;
		this->x = other.x; this->y = other.y;
		this->sprite.setTexture(this->texture);
		this->sprite.setOrigin(0, this->sprite.getLocalBounds().height);
		this->sprite.setPosition(this->x, this->y);
		this->is_collidable = other.is_collidable;
		this->hitbox = other.hitbox;
	}
	return *this;
}

bool Block::collidable() const
{
	return is_collidable;
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
