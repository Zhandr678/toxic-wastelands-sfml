#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Constants.h"

class Block
{
private:
	uint16_t id;
	sf::String file;
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	bool is_collidable;
	sf::FloatRect hitbox;
	float height, width;
	float x, y;
public:
	friend class Engine;
	Block();
	Block(uint16_t id, std::string file, float x, float y, bool is_collidable);
	Block(const Block& other);
	Block& operator =(const Block& other);

	bool collidable() const;
	uint16_t get_id() const;
	void create_mask_from_color(sf::Color color);
	void draw(sf::RenderWindow& window) const;
	sf::FloatRect get_hitbox() const;
	
	~Block() {};
};

