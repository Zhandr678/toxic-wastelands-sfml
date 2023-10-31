#pragma once
#include <SFML/Graphics.hpp>

#include "Entity.h"

class NPC : public Entity
{
private:
	float panic = 0.0f, hearing_radius = 160.0f, sight_angle = 60.0f;
public:
	NPC() = delete;
	NPC(uint16_t id, std::string path, float x, float y, float height = TILE_SIZE, float width = TILE_SIZE, float speed = DEFAULT_SPEED, float MAX_HP = DEFAULT_MAX_HP, float hp = DEFAULT_MAX_HP);

	void control(float& time) override;
	void take_damage(float amount) override;
	void heal(float amount) override;

	void draw_hearing_circle(sf::RenderWindow& window);
	void draw_seeing_lines(sf::RenderWindow& window);

	void hearing();
	void seeing();
	void increase_panic(float amount);
	void decrease_panic(float amount);
};

