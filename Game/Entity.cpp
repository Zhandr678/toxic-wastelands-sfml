#include "Entity.h"
#include <iostream>

Entity::Entity(uint16_t id, std::string path, float x, float y, float height, float width, float speed, float MAX_HP, float hp) :
	id(id), x(x), y(y), speed(speed), height(height), width(width)
{
	this->image.loadFromFile(path);
	this->image.createMaskFromColor(sf::Color::White);
	this->texture.loadFromImage(this->image);
	this->sprite.setTexture(this->texture);
	this->sprite.setTextureRect(sf::IntRect(48 * static_cast <int>(this->current_frame), 0, this->width, this->height));
	this->sprite.setPosition(this->x, this->y);
}

void Entity::move(float& time)
{
	if (!is_alive()) { return; }
	this->x += this->dx * time;
	this->y += this->dy * time;

	this->change_position(x, y);
	this->HPBar->move(this->x - 10.0f, this->y - 10.0f, false);
}

void Entity::attack(float& time)
{
	isAttacking = true;
	float temp = 1.2 * time;
	this->frame_move(temp);
	if (get_current_frame() >= 6) { isAttacking = false; this->set_frame(0); }
	this->sprite.setTextureRect(sf::IntRect(48 * static_cast <int>(this->get_current_frame()), 179, this->get_size().x, this->get_size().y));
}

void Entity::apply_gravity(float& time)
{
	if (!this->onGround)
	{
		this->dy += this->gravity * time;
		this->isJumping = true;
	}
}

void Entity::collisions(const Map& map, float& time)
{
	if (this->dy > 0 and (map.intersects_with_type(this->x + 2.0f, this->y + this->height + 1.8 * this->dy, Texture_Type::COLLIDABLE_TILE)
		or map.intersects_with_type(this->x + this->width - 2.0f, this->y + this->height + 1.8 * this->dy, Texture_Type::COLLIDABLE_TILE)))
	{
		if (this->dy > UNHARMFUL_Y_SPEED)
		{
			float damage = DAMAGE_RATE_PER_SPEED * pow(this->dy, DAMAGE_POWER_PER_SPEED);
			this->take_damage(damage, time);
		}
		if (this->dy < 0.5) { this->dy = 0; }
		this->dy -= 0.8 * this->dy;
	}
	if ((map.intersects_with_type(this->x + 2.0f, this->y + this->height, Texture_Type::COLLIDABLE_TILE)
		or map.intersects_with_type(this->x + this->width - 2.0f, this->y + this->height, Texture_Type::COLLIDABLE_TILE)))
	{
		this->set_on_ground();
		this->set_not_jumping();
	}
	else
	{
		this->set_off_ground();
		this->set_jumping();
	}
	if (this->dx > 0 and (map.intersects_with_type(this->x + this->width, this->y + 2.0f, Texture_Type::COLLIDABLE_TILE)
		or map.intersects_with_type(this->x + this->width, this->y + this->height - 2.0f, Texture_Type::COLLIDABLE_TILE)))
	{
		this->dx = 0;
	}
	if (this->dx < 0 and (map.intersects_with_type(this->x, this->y + 2.0f, Texture_Type::COLLIDABLE_TILE)
		or map.intersects_with_type(this->x, this->y + this->height - 2.0f, Texture_Type::COLLIDABLE_TILE)))
	{
		this->dx = 0;
	}

	if (this->dy < 0 and (map.intersects_with_type(this->x + 2.0f, this->y, Texture_Type::COLLIDABLE_TILE)
		or map.intersects_with_type(this->x + this->width - 2.0f, this->y, Texture_Type::COLLIDABLE_TILE)))
	{
		this->dy = 0;
	}
}

void Entity::die(float& time)
{
	this->isAlive = false;
	this->dying = true;
}

void Entity::play_dying_animation(float& time)
{
	if (!dying) { return; }
	float temp = 0.5 * time;
	this->frame_move(temp);
	if (get_current_frame() >= 5) { dying = false; set_frame(5); }
	this->sprite.setTextureRect(sf::IntRect(48 * static_cast <int>(this->get_current_frame()), 128, this->get_size().x, this->get_size().y));
}

void Entity::draw_hitbox(sf::RenderWindow& window)
{
	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(this->width, this->height));
	rect.setPosition(this->x, this->y);
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineThickness(1.0f);
	rect.setOutlineColor(sf::Color::Yellow);
	window.draw(rect);
}

void Entity::change_position(float x, float y)
{
	this->x = x; this->y = y;
	this->sprite.setPosition(this->x, this->y);
	this->HPBar->move(this->x - 10.0f, this->y - 10.0f, false);
}

void Entity::draw(sf::RenderWindow& window)
{
	window.draw(this->sprite);
}

void Entity::draw_health(sf::RenderWindow& window)
{
	this->HPBar->draw(window);
}

bool Entity::is_alive() const
{
	return this->isAlive;
}

bool Entity::is_jumping() const
{
	return this->isJumping;
}

bool Entity::is_on_ground() const
{
	return this->onGround;
}

void Entity::set_on_ground()
{
	this->onGround = true;
}

void Entity::set_off_ground()
{
	this->onGround = false;
}

void Entity::set_jumping()
{
	this->isJumping = true;
}

void Entity::set_not_jumping()
{
	this->isJumping = false;
}

sf::Vector2f Entity::get_size() const
{
	return sf::Vector2f(this->width, this->height);
}

float Entity::get_gravity_value() const
{
	return this->gravity;
}

float Entity::get_speed_value() const
{
	return this->speed;
}

float Entity::get_current_frame() const
{
	return this->current_frame;
}

void Entity::frame_move(float& time)
{
	this->current_frame += 0.005 * time;
}

void Entity::frame_clear()
{
	this->current_frame = 0.0f;
}

void Entity::set_frame(float value)
{
	this->current_frame = value;
}

bool Entity::is_dying() const
{
	return dying;
}

sf::Vector2f Entity::get_position() const
{
	return sf::Vector2f(this->x, this->y);
}

void Entity::init_HPBar(float x, float y, float length, float height, HPBar_Display format, sf::Color color, float MAX_HP, float HP)
{
	this->HPBar = new HealthBar(x, y, length, height, format, color, MAX_HP, HP);
}

Entity::~Entity()
{
	delete this->HPBar;
};