#pragma once
#include <SFML/Graphics.hpp>

class Block
{
private:
	uint16_t id;
	sf::String file;
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	size_t length, width;
	size_t x, y;
public:
	Block() = delete;
	Block(uint16_t id, sf::String file, float x, float y);

	void create_mask_from_color(sf::Color color);
	void draw(sf::RenderWindow& window);
	
	~Block() {};
};

