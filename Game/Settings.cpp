#include "Settings.h"

Settings::Settings()
{
	this->movement.insert({ sf::Keyboard::Up, Entity_State::JUMP });
	this->movement.insert({ sf::Keyboard::Right, Entity_State::MOVING_RIGHT });
	this->movement.insert({ sf::Keyboard::Left, Entity_State::MOVING_LEFT });
	this->movement.insert({ sf::Keyboard::Space, Entity_State::JUMP });
}

Settings::Settings(std::map<sf::Keyboard::Key, Entity_State> movement) :
	movement(movement)
{
}

Settings::Settings(const Settings& other)
{
	this->movement = other.movement;
}

Settings& Settings::operator=(const Settings& other)
{
	if (this != &other)
	{
		this->movement = other.movement;
	}
	return *this;
}

Entity_State Settings::on_pressed(sf::Keyboard::Key key) const
{
	return this->movement.at(key);
}

void Settings::set_key_responsibility(sf::Keyboard::Key key, Entity_State movement)
{
	this->movement[key] = movement;
}

void Settings::__init__(std::map<sf::Keyboard::Key, Entity_State> movement)
{
	this->movement = movement;
}
