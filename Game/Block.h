#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Constants.h"

class Block;
Block __NULL_BLOCK__();

class Block
{
private:
	uint16_t id;
	sf::String file;
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::FloatRect hitbox;
	float height, width;
	float x, y;
	bool is_null = false;
public:
	friend class Engine;
	friend Block __NULL_BLOCK__();

	Block() = delete;
	Block(uint16_t id, std::string file, float x, float y);
	Block(const Block& other);
	Block& operator =(const Block& other);

	uint16_t get_id() const;
	void create_mask_from_color(sf::Color color);
	void draw(sf::RenderWindow& window) const;
	sf::FloatRect get_hitbox() const;
	bool contains(float x, float y) const;
	
	std::pair <float, float> get_pos() const;

	~Block() {};
};