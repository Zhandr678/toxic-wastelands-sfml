#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Constants.h"
#include "Block.h"

class Map
{
private:
	std::vector <std::vector <Block>> grid;
	sf::Image background_image;
	sf::Texture background_texture;
	sf::Sprite background_sprite;
public:
	Map(std::vector <sf::String> background_files, std::vector <std::vector <sf::String>> block_files);

	void draw(sf::RenderWindow& window);
	void update_block(float x, float y, sf::String new_block);
	void update_block(int x, int y, sf::String new_block);



	~Map() {};
};

