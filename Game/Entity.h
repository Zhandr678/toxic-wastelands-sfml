#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Constants.h"
#include "HealthBar.h"

class Entity
{
private:
	friend class Engine;

	enum class State
	{
		IDLE, MOVING_RIGHT, MOVING_LEFT, JUMP
	};

	HealthBar HP;
	uint16_t id;
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	float x, y, dx = 0, dy = 0, height, width;
	float speed, current_frame = 0;
	float gravity = DEFAULT_GRAVITY;
	bool isAlive = true, facing_right = true, onGround = true, isJumping = false;
	State state = State::IDLE;
	sf::FloatRect hitbox;
public:
	Entity() = delete;
	Entity(uint16_t id, std::string path, float x, float y, float height = TILE_SIZE, float width = TILE_SIZE, float speed = DEFAULT_SPEED, float MAX_HP = DEFAULT_MAX_HP, float hp = DEFAULT_MAX_HP);

	virtual void control(float time);
	virtual void move(float& time);

	void draw_hitbox(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
	void draw_health(sf::RenderWindow& window);

	void change_position(float x, float y);
	void take_damage(float amount);
	void heal(float amount);
	void apply_gravity(float& time);
	//void adjust_position();
	bool hitbox_intersects(sf::FloatRect other);
	bool is_alive();

	virtual ~Entity();
};

