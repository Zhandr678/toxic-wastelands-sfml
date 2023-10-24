#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"

class HealthBar
{
private:
	float max_hp, hp;
	float bar_length, bar_height;
	float x, y;
	sf::RectangleShape full_bar, health;

	void update_bar(float to);
public:
	friend class Engine;

	HealthBar() = default;
	HealthBar(float x, float y, float bar_length, float bar_height, float MAX_HP = DEFAULT_MAX_HP, float HP = DEFAULT_MAX_HP);
	HealthBar(const HealthBar& other);
	HealthBar& operator=(const HealthBar& other);

	void draw(sf::RenderWindow& window) const;
	void take_damage(float amount);
	void heal(float amount);
	~HealthBar() {};
};

