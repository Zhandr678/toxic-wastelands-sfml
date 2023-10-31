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
	sf::Color color;
	HPBar_Display format;

	void update_bar(float to);
public:
	friend class Engine;

	HealthBar() = delete;
	HealthBar(float x, float y, float bar_length, float bar_height, HPBar_Display format, sf::Color color = sf::Color::Red, float MAX_HP = DEFAULT_MAX_HP, float HP = DEFAULT_MAX_HP);
	HealthBar(const HealthBar& other);
	HealthBar& operator=(const HealthBar& other);

	void change_color(sf::Color color);
	void draw(sf::RenderWindow& window) const;
	void take_damage(float amount);
	void heal(float amount);
	~HealthBar() {};
};

