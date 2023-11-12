#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <functional>

#include "Constants.h"
#include "HealthBar.h"
#include "Entity.h"
#include "Settings.h"

class Engine;

class Hero : public Entity
{
private:
	friend class Engine;
	Settings movement;
public:
	Hero() = delete;
	Hero(uint16_t id, std::string path, float x, float y, float height = TILE_SIZE, float width = TILE_SIZE, float speed = DEFAULT_SPEED, float MAX_HP = DEFAULT_MAX_HP, float hp = DEFAULT_MAX_HP);

	virtual sf::FloatRect control(const Map& map, float& time, Entity* entity) override;

	virtual void take_damage(float amount, float& time) override;
	virtual void heal(float amount) override;
};

