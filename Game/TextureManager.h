#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <nlohmann/json.hpp>
#include <vector>
#include <fstream>
#include <iostream>

#include "Constants.h"
#include "Block.h"

class TextureManager
{
private:
	std::string textures_canonical_path;
public:
	TextureManager() = delete;
	TextureManager(const TextureManager& other) = delete;
	TextureManager& operator =(const TextureManager& other) = delete;
	TextureManager(char** argv);

	std::string texture_path() const;
	std::vector <std::vector <Block>> get_layers_from_json(std::string path);
	nlohmann::json&& parse_to_json(std::string file);
	std::string get_file_from_id(uint16_t id, Texture_Type type);

	~TextureManager() {};
};