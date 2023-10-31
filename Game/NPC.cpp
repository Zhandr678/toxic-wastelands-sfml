#include "NPC.h"

NPC::NPC(uint16_t id, std::string path, float x, float y, float height, float width, float speed, float MAX_HP, float hp) :
	Entity(id, path, x, y, height, width, speed, MAX_HP, hp)
{
	this->HPBar = new HealthBar(800.0f, 5.0f, 96.0f, 16.0f, HPBar_Display::FIXED);
}

void NPC::control(float& time)
{

}

void NPC::take_damage(float amount)
{
	this->HPBar->take_damage(amount);
}

void NPC::heal(float amount)
{
	this->HPBar->heal(amount);
}

void NPC::draw_hearing_circle(sf::RenderWindow& window)
{
	sf::CircleShape circle;
	circle.setPosition(this->get_position().x - hearing_radius + this->get_size().x / 2.0f, this->get_position().y - hearing_radius + this->get_size().y / 2.0f);
	circle.setRadius(this->hearing_radius);
	circle.setFillColor(sf::Color::Transparent);
	circle.setOutlineColor(sf::Color::Yellow);
	circle.setOutlineThickness(1.0f);
	window.draw(circle);
}

void NPC::draw_seeing_lines(sf::RenderWindow& window)
{
	sf::Vertex line[2];
	line[0].position = sf::Vector2f(this->get_position().x + this->get_size().x / 2.0f, this->get_position().y + 3.0f);
	line[0].color = sf::Color::Green;
	if (this->facing_right) 
	{
		
		line[1].position = sf::Vector2f(line[0].position.x + 500.0f, line[0].position.y);
		line[1].color = sf::Color::Green;
	}
	else 
	{
		line[1].position = sf::Vector2f(line[0].position.x - 500.0f, line[0].position.y);
		line[1].color = sf::Color::Green;
	}
	window.draw(line, 2, sf::Lines);
}

void NPC::hearing()
{

}

void NPC::seeing()
{

}

void NPC::increase_panic(float amount)
{
	panic = std::min(100.0f, panic + amount);
}

void NPC::decrease_panic(float amount)
{
	panic = std::max(0.0f, panic - amount);
}
