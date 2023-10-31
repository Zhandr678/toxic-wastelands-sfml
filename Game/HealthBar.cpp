#include "HealthBar.h"

void HealthBar::update_bar(float to)
{
	float new_width = (to / max_hp) * bar_length - 1.0f;
	health.setSize(sf::Vector2f(new_width, this->bar_height - 2.0f));
	health.setFillColor(color);
}

HealthBar::HealthBar(float x, float y, float bar_length, float bar_height, HPBar_Display format, sf::Color color, float MAX_HP, float HP) :
	x(x), y(y), max_hp(MAX_HP), hp(HP), bar_length(bar_length), bar_height(bar_height), color(color), format(format)
{
	full_bar.setSize(sf::Vector2f(this->bar_length, this->bar_height));
	full_bar.setPosition(this->x, this->y);
	full_bar.setFillColor(sf::Color::Transparent);
	full_bar.setOutlineThickness(1.0f);
	sf::Color grey;
	grey.r = 128; grey.g = 128; grey.b = 128;
	full_bar.setOutlineColor(grey);

	health.setSize(sf::Vector2f(this->bar_length - 2.0f, this->bar_height - 2.0f));
	health.setPosition(this->x + 1.0f, this->y + 1.0f);
	health.setFillColor(color);
}

HealthBar::HealthBar(const HealthBar& other) :
	x(other.x), y(other.y), max_hp(other.max_hp), hp(other.hp), bar_length(other.bar_length), bar_height(other.bar_height), color(other.color), format(other.format)
{
	full_bar.setSize(sf::Vector2f(this->bar_length, this->bar_height));
	full_bar.setPosition(this->x, this->y);
	full_bar.setFillColor(sf::Color::Transparent);
	full_bar.setOutlineThickness(1.0f);
	sf::Color grey;
	grey.r = 128; grey.g = 128; grey.b = 128;
	full_bar.setOutlineColor(grey);

	health.setSize(sf::Vector2f(this->bar_length - 2.0f, this->bar_height - 2.0f));
	health.setPosition(this->x + 1.0f, this->y + 1.0f);
	health.setFillColor(color);
}

HealthBar& HealthBar::operator=(const HealthBar& other)
{
	if (this != &other)
	{
		this->x = other.x; this->y = other.y;
		this->max_hp = other.max_hp;
		this->hp = other.hp;
		this->bar_height = other.bar_height;
		this->bar_length = other.bar_length;
		this->color = other.color;
		this->format = other.format;

		full_bar.setSize(sf::Vector2f(this->bar_length, this->bar_height));
		full_bar.setPosition(this->x, this->y);
		full_bar.setFillColor(sf::Color::Transparent);
		full_bar.setOutlineThickness(1.0f);
		sf::Color grey;
		grey.r = 128; grey.g = 128; grey.b = 128;
		full_bar.setOutlineColor(grey);

		health.setSize(sf::Vector2f(this->bar_length - 2.0f, this->bar_height - 2.0f));
		health.setPosition(this->x + 1.0f, this->y + 1.0f);
		health.setFillColor(color);
	}
	return *this;
}

void HealthBar::change_color(sf::Color color)
{
	this->color = color;
	health.setFillColor(color);
}

void HealthBar::draw(sf::RenderWindow& window) const
{
	window.draw(full_bar);
	window.draw(health);
}

void HealthBar::take_damage(float amount)
{
	hp = std::max(0.0f, hp - amount);
	update_bar(hp);
}

void HealthBar::heal(float amount)
{
	hp = std::min(max_hp, hp + amount);
	update_bar(hp);
}
