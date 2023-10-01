#include "Entity.h"
#include <iostream>

Entity::Entity(sf::String file_path, double x, double y)
{
	this->file_path = file_path;
	try {
		this->image.loadFromFile(file_path);
		this->image.createMaskFromColor(sf::Color::White);
		this->texture.loadFromImage(this->image);
		this->sprite.setTexture(this->texture);
	}
	catch (const std::exception& e)
	{
		std::cout << "[SFML error] -> " << e.what() << std::endl;
	}

	this->x = x; this->y = y;
	this->HP = MAX_HEALTH;
	this->is_alive = true;
}

Entity::Entity(sf::String file_path, double x, double y, uint8_t HP)
{
	this->file_path = file_path;
	try {
		this->image.loadFromFile(file_path);
		this->image.createMaskFromColor(sf::Color::White);
		this->texture.loadFromImage(this->image);
		this->sprite.setTexture(this->texture);
	}
	catch (const std::exception& e)
	{
		std::cout << "[SFML error] -> " << e.what() << std::endl;
	}
	
	this->x = x; this->y = y;
	if (HP <= 0) 
	{ 
		this->is_alive = false;  
		this->HP = 0;
	}
	this->HP = HP;
	this->is_alive = true;
}

uint64_t Entity::get_id()
{
	return this->id;
}

void Entity::take_damage(uint8_t amount)
{

}

void Entity::heal(uint8_t amount)
{

}
