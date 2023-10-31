#pragma once
#include <SFML/Graphics.hpp>
#include <string>

#include "Constants.h"
#include "HealthBar.h"
#include "Map.h"

class Entity
{
private:
	uint16_t id;
	sf::Image image;
	sf::Texture texture;
	float x, y, height, width, speed, gravity = DEFAULT_GRAVITY;
	float current_frame = 0;
	bool isAlive = true;
protected:
	sf::Sprite sprite;
	Entity_State state = Entity_State::IDLE;
	HealthBar* HPBar = nullptr;
	bool facing_right = true, onGround = true, isJumping = false;
	float dx = 0, dy = 0;
public:
	/* Initializers */
	Entity() = delete;
	Entity(uint16_t id, std::string path, float x, float y, float height = TILE_SIZE, float width = TILE_SIZE, float speed = DEFAULT_SPEED, float MAX_HP = DEFAULT_MAX_HP, float hp = DEFAULT_MAX_HP);
	void init_HPBar(float x, float y, float length, float height, HPBar_Display format, sf::Color color = sf::Color::Red, float MAX_HP = DEFAULT_MAX_HP, float HP = DEFAULT_MAX_HP);

	/* Virtuals */
	virtual void control(float& time) = 0;
	virtual void take_damage(float amount) = 0;
	virtual void heal(float amount) = 0;
	virtual void move(float& time);

	/* Common Interfaces */
	void draw_hitbox(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
	void draw_health(sf::RenderWindow& window);

	void change_position(float x, float y);
	void apply_gravity(float& time);

	void collisions(const Map& map);

	/* Getters and Setters */
	bool is_alive() const;
	bool is_jumping() const;
	bool is_on_ground() const;

	void set_on_ground();
	void set_off_ground();

	void set_jumping();
	void set_not_jumping();

	sf::Vector2f get_size() const;
	sf::Vector2f get_position() const;

	float get_gravity_value() const;
	float get_speed_value() const;
	float get_current_frame() const;

	void frame_move(float& time);
	void frame_clear();

	virtual ~Entity();
};