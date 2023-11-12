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

	uint16_t push(EntityGroup group, std::string path, float x, float y, float height, float width, float speed, float max_hp, float hp, HPBar_Display display, sf::Color HPcolor, bool key);

	void rewrite(uint16_t id, EntityGroup group, std::string path, float x, float y, float height, float width, float speed, float max_hp, float hp, HPBar_Display display, sf::Color HPcolor);
	Entity* get_entity(uint16_t id);
	sf::FloatRect control(const Map& map, float& time, Entity* entity);
	void move(float& time);
	void check_collison(const Map& map, float& time);
	void draw(sf::RenderWindow& window, bool show_hitboxes, bool show_hearing, bool show_seeing);
	void apply_gravity(float& time);
	void take_damage(std::vector <uint16_t> felt, float amount, float& time);
	std::vector <uint16_t> check_fell_off(const Map& map);
	std::vector <uint16_t> is_dying();
	void play_dying_animation(std::vector <uint16_t> dies, float& time);
	std::vector <uint16_t> intersected(sf::FloatRect hit);

	~EntityManager();
};

