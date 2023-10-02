#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <nlohmann/json.hpp>
#include <vector>
#include <fstream>
#include <iostream>

#include "Constants.h"
#include "Block.h"
#include "Layer.h"
#include "Map.h"

class TextureManager
{
private:
	std::string textures_canonical_path;
	
	std::string get_file_from_id(uint16_t id, Texture_Type type);
	nlohmann::json&& parse_to_json(std::string file);
	std::vector <Layer> get_layers_from_json(std::string path);
	Texture_Type get_type(std::string name);
public:
	TextureManager() = delete;
	TextureManager(const TextureManager& other) = delete;
	TextureManager& operator =(const TextureManager& other) = delete;
	TextureManager(char** argv);

	std::string texture_path() const;
	
	Map generate_map(std::string json_path, std::vector <std::string> background_files);

	~TextureManager() {};
};