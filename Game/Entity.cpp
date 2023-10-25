#include "Entity.h"
#include <iostream>

Entity::Entity(uint16_t id, std::string path, float x, float y, float speed, float MAX_HP, float hp, float height, float width) :
	id(id), x(x), y(y), speed(speed), MAX_HP(MAX_HP), hp(hp), height(height), width(width)
{
	this->image.loadFromFile(path);
	this->image.createMaskFromColor(sf::Color::White);
	this->texture.loadFromImage(this->image);
	this->sprite.setTexture(this->texture);
	this->sprite.setTextureRect(sf::IntRect(48 * static_cast <int>(this->current_frame), 0, this->width, this->height));
	this->sprite.setPosition(this->x, this->y);
	this->hitbox = sf::FloatRect(this->x, this->y, this->width, this->height);
}

void Entity::control(float time)
{
	if (!this->facing_right) {
		sf::Vector2f currentPosition = sprite.getPosition();
		sprite.setOrigin(sprite.getLocalBounds().width, 0);
		sprite.setScale({ -1, 1 });
		sprite.setPosition(currentPosition);
	}
	else {
		// Set the origin back to the default (left side of the sprite)
		sprite.setOrigin(0, 0);

		// Reset the scale to normal
		sprite.setScale({ 1, 1 });
	}

	bool key_pressed = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		this->dx = this->speed;
		this->state = State::MOVING_RIGHT;
		this->current_frame += 0.005 * time;
		this->facing_right = true;
		if (this->current_frame > 6) { current_frame -= 6; }
		sprite.setTextureRect(sf::IntRect(48 * static_cast <int>(this->current_frame), 34, this->width, this->height));
		key_pressed = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		this->dx = -1 * this->speed;
		this->state = State::MOVING_LEFT;
		this->current_frame += 0.005 * time;	
		this->facing_right = false;
		if (this->current_frame > 6) { current_frame -= 6; }
		sprite.setTextureRect(sf::IntRect(48 * static_cast <int>(this->current_frame), 34, this->width, this->height));
		key_pressed = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		this->dy = -1 * this->speed;
		key_pressed = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		this->dy = 1 * this->speed;
		key_pressed = true;
	}
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) and this->onGround)
	{
		this->dy = -3 * this->speed;
		this->state = State::JUMP;
		this->onGround = false;
	}*/
	if (!key_pressed)
	{
		this->sprite.setTextureRect(sf::IntRect(0, 0, this->width, this->height));
		dx = 0; dy = 0;
	}
}

void Entity::move(float time)
{
	this->x += this->dx * time;
	this->y += this->dy * time;
	//apply_gravity(time);

	this->change_position(this->x, this->y);
}

void Entity::draw(sf::RenderWindow& window)
{
	window.draw(this->sprite);
}

void Entity::change_position(float x, float y)
{
	this->x = x; this->y = y;
	this->hitbox.top = y;
	this->hitbox.left = x;
	this->sprite.setPosition(this->x, this->y);
}

void Entity::take_damage(float amount)
{
	this->hp -= amount;
	if (this->hp < 0) { this->isAlive = false; }
}

void Entity::heal(float amount)
{
	this->hp += amount;
	this->hp = std::min(this->hp, this->MAX_HP);
}

void Entity::apply_gravity(float time)
{
	this->dy += this->gravity * time;
}

bool Entity::hitbox_intersects(sf::FloatRect other)
{
	return this->hitbox.intersects(other);
}

bool Entity::is_alive()
{
	return isAlive;
}

Entity::~Entity() {};
