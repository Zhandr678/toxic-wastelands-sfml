#include "Entity.h"
#include <iostream>

Entity::Entity(uint16_t id, std::string path, float x, float y, float height, float width, float speed, float MAX_HP, float hp) :
	id(id), x(x), y(y), speed(speed), height(height), width(width)
{
	this->image.loadFromFile(path);
	this->image.createMaskFromColor(sf::Color::White);
	this->texture.loadFromImage(this->image);
	this->sprite.setTexture(this->texture);
	this->sprite.setTextureRect(sf::IntRect(48 * static_cast <int>(this->current_frame), 4, this->width, this->height));
	this->sprite.setPosition(this->x, this->y);
	this->HPBar = new HealthBar(5.0f, 5.0f, 96.0f, 16.0f, HPBar_Display::FIXED);
}

void Entity::move(float& time)
{
	this->x += this->dx * time;
	this->y += this->dy * time;

	this->change_position(x, y);
}

void Entity::apply_gravity(float& time)
{
	if (!this->onGround)
	{
		this->dy += this->gravity * time;
		this->isJumping = true;
	}
}

void Entity::collisions(const Map& map)
{
	sf::Vector2f pos = this->get_position(), size = this->get_size();
	if (this->get_dy() > 0 and (map.intersects_with_type(pos.x + 2.0f, pos.y + size.y + 1.8 * this->get_dy(), Texture_Type::COLLIDABLE_TILE)
		or map.intersects_with_type(pos.x + size.x - 2.0f, pos.y + size.y + 1.8 * this->get_dy(), Texture_Type::COLLIDABLE_TILE)))
	{
		std::cout << this->get_dy() << " ";
		if (this->get_dy() > UNHARMFUL_Y_SPEED)
		{
			float damage = DAMAGE_RATE_PER_SPEED * pow(this->get_dy(), DAMAGE_POWER_PER_SPEED);
			this->take_damage(damage);
			std::cout << damage << "\n";
		}
		if (this->get_dy() < 0.5) { this->set_dy(0); }
		this->set_dy(this->get_dy() - 0.8 * this->get_dy());
	}
	if ((map.intersects_with_type(pos.x + 2.0f, pos.y + size.y, Texture_Type::COLLIDABLE_TILE)
		or map.intersects_with_type(pos.x + size.x - 2.0f, pos.y + size.y, Texture_Type::COLLIDABLE_TILE)))
	{
		this->set_on_ground(true);
		this->set_jumping(false);
	}
	else
	{
		this->set_on_ground(false);
		this->set_jumping(true);
	}
	if (this->get_dx() > 0 and (map.intersects_with_type(pos.x + size.x, pos.y + 2.0f, Texture_Type::COLLIDABLE_TILE)
		or map.intersects_with_type(pos.x + size.x, pos.y + size.y - 2.0f, Texture_Type::COLLIDABLE_TILE)))
	{
		this->set_dx(0);
	}
	if (this->get_dx() < 0 and (map.intersects_with_type(pos.x, pos.y + 2.0f, Texture_Type::COLLIDABLE_TILE)
		or map.intersects_with_type(pos.x, pos.y + size.y - 2.0f, Texture_Type::COLLIDABLE_TILE)))
	{
		this->set_dx(0);
	}

	if (this->get_dy() < 0 and (map.intersects_with_type(pos.x + 2.0f, pos.y, Texture_Type::COLLIDABLE_TILE)
		or map.intersects_with_type(pos.x + size.x - 2.0f, pos.y, Texture_Type::COLLIDABLE_TILE)))
	{
		this->set_dy(0);
	}
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

bool Entity::is_facing_right() const
{
	return facing_right;
}

bool Entity::is_facing_left() const
{
	return !facing_right;
}

void Entity::set_on_ground(bool is)
{
	this->onGround = is;
}

void Entity::set_jumping(bool is)
{
	this->isJumping = is;
}

float Entity::get_dx() const
{
	return this->dx;
}

float Entity::get_dy() const
{
	return this->dy;
}

sf::Vector2f Entity::get_size() const
{
	return sf::Vector2f(this->width, this->height);
}

void Entity::set_dy(float speed)
{
	this->dy = speed;
}

void Entity::set_dx(float speed)
{
	this->dx = speed;
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

sf::Vector2f Entity::get_position() const
{
	return sf::Vector2f(this->x, this->y);
}

Entity_State Entity::get_state() const
{
	return this->state;
}

void Entity::set_state(Entity_State state)
{
	this->state = state;
}

void Entity::set_facing_right(bool is)
{
	this->facing_right = is;
}

sf::Sprite& Entity::this_sprite()
{
	return this->sprite;
}

HealthBar* Entity::this_HPBar()
{
	return this->HPBar;
}

void Entity::frame_move_by(float val)
{
	current_frame += val;
}

void Entity::init_HPBar(float x, float y, float length, float height, HPBar_Display format, sf::Color color, float MAX_HP, float HP)
{
	this->HPBar = new HealthBar(x, y, length, height, format, color, MAX_HP, HP);
}

Entity::~Entity()
{
	delete this->HPBar;
};