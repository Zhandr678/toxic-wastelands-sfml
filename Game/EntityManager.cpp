#include "EntityManager.h"

uint16_t EntityManager::id;

EntityManager::EntityManager()
{
}

uint16_t EntityManager::push(EntityGroup group, std::string path, float x, float y, float height, float width, float speed, float max_hp, float hp, HPBar_Display display, sf::Color HPcolor, bool key)
{
	if (key) { 
		entities[666] = new NPC(id, path, x, y, height, width, speed, max_hp, hp, display, HPcolor); 
		return 666;
	}
	else {
		entities[id] = new NPC(id, path, x, y, height, width, speed, max_hp, hp, display, HPcolor);
		id++; return id - 1;
	}
	
}

void EntityManager::rewrite(uint16_t id, EntityGroup group, std::string path, float x, float y, float height, float width, float speed, float max_hp, float hp, HPBar_Display display, sf::Color HPcolor)
{
	delete entities[id];
	entities[id] = new NPC(id, path, x, y, height, width, speed, max_hp, hp, display, HPcolor);
}

Entity* EntityManager::get_entity(uint16_t id)
{
	return entities[id];
}

sf::FloatRect EntityManager::control(const Map& map, float& time, Entity* entity)
{
	sf::FloatRect attack;
	for (const auto& i : entities)
	{
		auto hit = i.second->control(map, time, entity);
		if (hit != sf::FloatRect(0, 0, 0, 0)) { attack = hit; }
	}
	return attack;
}

void EntityManager::move(float& time)
{
	for (const auto& i : entities)
	{
		i.second->move(time);
	}
}

void EntityManager::check_collison(const Map& map, float& time)
{
	for (const auto& i : entities)
	{
		i.second->collisions(map, time);
	}
}

void EntityManager::draw(sf::RenderWindow& window, bool show_hitboxes, bool show_hearing, bool show_seeing)
{
	for (const auto& i : entities)
	{
		i.second->draw(window);
		i.second->draw_health(window);
		if (show_hitboxes) { i.second->draw_hitbox(window); }
		if (show_hearing) 
		{
			if (NPC* d = dynamic_cast <NPC*>(i.second))
			{
				d->draw_hearing_circle(window);
			}
		}
		if (show_seeing)
		{
			if (NPC* d = dynamic_cast <NPC*>(i.second))
			{
				d->draw_seeing_lines(window);
			}
		}
	}
}

void EntityManager::apply_gravity(float& time)
{
	for (const auto& i : entities)
	{
		i.second->apply_gravity(time);
	}
}

void EntityManager::take_damage(std::vector <uint16_t> felt, float amount, float& time)
{
	for (const auto& i : felt)
	{
		entities[i]->take_damage(amount, time);
	}
}

std::vector <uint16_t> EntityManager::check_fell_off(const Map& map)
{
	std::vector <uint16_t> felt;
	for (const auto& i : entities)
	{
		if (i.second->get_position().y + i.second->get_size().y >= map.get_y_boundaries().y - TILE_SIZE) {
			felt.push_back(i.first);
		}
	}
	return felt;
}

std::vector <uint16_t> EntityManager::is_dying()
{
	std::vector <uint16_t> died;
	for (const auto& i : entities)
	{
		if (i.second->is_dying())
		{
			died.push_back(i.first);
		}
	}
	return died;
}

void EntityManager::play_dying_animation(std::vector<uint16_t> dies, float& time)
{
	for (const auto& i : dies)
	{
		entities[i]->play_dying_animation(time);
	}
}

std::vector<uint16_t> EntityManager::intersected(sf::FloatRect hit)
{
	std::vector <uint16_t> hitt;
	for (const auto& i : entities)
	{
		if (i.second->intersects(hit)) { hitt.push_back(i.first); }
	}
	return hitt;
}

EntityManager::~EntityManager()
{
	for (const auto& i : entities)
	{
		delete i.second;
	}
}
