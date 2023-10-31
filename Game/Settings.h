#pragma once
#include <SFML/Graphics.hpp>
#include <map>

#include "Constants.h"

class Settings
{
private:
	std::map <sf::Keyboard::Key, Entity_State> movement;
public:
	Settings();
	Settings(std::map <sf::Keyboard::Key, Entity_State> movement);

	Settings(const Settings& other);
	Settings& operator =(const Settings& other);

	Entity_State on_pressed(sf::Keyboard::Key key) const;
	void set_key_responsibility(sf::Keyboard::Key key, Entity_State movement);
	void __init__(std::map <sf::Keyboard::Key, Entity_State> movement);
};

