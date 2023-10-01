#pragma once
#include <SFML/Graphics.hpp>

#define MAX_HEALTH 100

enum class Movement
{
	IDLE, WALK, RUN, ATTACK, HURT, JUMP, RECHARGE, SHOT, DEAD
};

class Entity
{
private:
	uint64_t id;
	sf::String file_path;
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	uint8_t HP, mass;
	bool is_alive;
	double x, y;
public:
	Entity() = delete;
	Entity(sf::String file_path, double x, double y);
	Entity(sf::String file_path, double x, double y, uint8_t HP);
	virtual void move(Movement value) = 0;
	virtual void jump() = 0;
	virtual double slowness_value() = 0;
	virtual double overweight_value() = 0;
	void take_damage(uint8_t amount);
	void heal(uint8_t amount);
	virtual void play_dying_animation();
	uint64_t get_id();

	~Entity() {};
};
