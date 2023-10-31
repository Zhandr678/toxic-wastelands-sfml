#pragma once
#include <SFML/Graphics.hpp>
#include <string>

#include "Constants.h"
#include "HealthBar.h"
#include "Map.h"

class Entity
{
private:
	HealthBar* HPBar = nullptr;
	uint16_t id;
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	float x, y, dx = 0, dy = 0, height, width, speed, gravity = DEFAULT_GRAVITY;;
	float current_frame = 0;
	bool isAlive = true, facing_right = true, onGround = true, isJumping = false;
	Entity_State state = Entity_State::IDLE;
public:
	Entity() = delete;
	Entity(uint16_t id, std::string path, float x, float y, float height = TILE_SIZE, float width = TILE_SIZE, float speed = DEFAULT_SPEED, float MAX_HP = DEFAULT_MAX_HP, float hp = DEFAULT_MAX_HP);

	virtual void control(float& time) = 0;
	virtual void move(float& time);
	virtual void take_damage(float amount) = 0;
	virtual void heal(float amount) = 0;

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
	bool is_facing_right() const;
	bool is_facing_left() const;

	void set_on_ground(bool is);
	void set_jumping(bool is);

	float get_dx() const;
	float get_dy() const;

	sf::Vector2f get_size() const;

	void set_dy(float speed);
	void set_dx(float speed);

	float get_gravity_value() const;
	float get_speed_value() const;
	float get_current_frame() const;

	sf::Vector2f get_position() const;

	Entity_State get_state() const;
	void set_state(Entity_State state);
	void set_facing_right(bool is);

	sf::Sprite& this_sprite();
	HealthBar* this_HPBar();

	void frame_move_by(float val);

	void init_HPBar(float x, float y, float length, float height, HPBar_Display format, sf::Color color = sf::Color::Red, float MAX_HP = DEFAULT_MAX_HP, float HP = DEFAULT_MAX_HP);

	virtual ~Entity();
};