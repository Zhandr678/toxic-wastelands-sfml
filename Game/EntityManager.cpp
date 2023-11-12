#include "EntityManager.h"

uint16_t EntityManager::id;

EntityManager::EntityManager()
{
}

void EntityManager::push(EntityGroup group, std::string path, float x, float y, float height, float width, float speed, float max_hp, float hp, HPBar_Display display, sf::Color HPcolor)
{
	entities[id] = new NPC(id, path, x, y, height, width, speed, max_hp, hp, display, HPcolor);
	id++;
}

Entity* EntityManager::get_entity(uint16_t id)
{
	return entities[id];
}

void EntityManager::control(const Map& map, float& time)
{
	for (const auto& i : entities)
	{
		i.second->control(map, time);
	}
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
		if (i.second->get_position().y + i.second->get_size().y >= map.get_y_boundaries().y) {
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

EntityManager::~EntityManager()
{
	for (const auto& i : entities)
	{
		delete i.second;
	}
}
