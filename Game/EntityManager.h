#pragma once
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "Constants.h"
#include "Hero.h"
#include "NPC.h"

class EntityManager
{
private:
	static uint16_t id;
	std::map <uint16_t, Entity*> entities;
public:
	EntityManager();

	void push(EntityGroup group, std::string path, float x, float y, float height, float width, float speed, float max_hp, float hp, HPBar_Display display, sf::Color HPcolor);

	Entity* get_entity(uint16_t id);
	void control(const Map& map, float& time);
	void move(float& time);
	void check_collison(const Map& map, float& time);
	void draw(sf::RenderWindow& window, bool show_hitboxes, bool show_hearing, bool show_seeing);
	void apply_gravity(float& time);
	void take_damage(std::vector <uint16_t> felt, float amount, float& time);
	std::vector <uint16_t> check_fell_off(const Map& map);
	std::vector <uint16_t> is_dying();
	void play_dying_animation(std::vector <uint16_t> dies, float& time);

	~EntityManager();
};

