#include "TextureManager.h"

TextureManager::TextureManager(char** argv)
{
    textures_canonical_path = std::filesystem::path(argv[0]).parent_path().string();
    textures_canonical_path = textures_canonical_path.substr(0, textures_canonical_path.find_last_of("/\\"));
    textures_canonical_path = textures_canonical_path.substr(0, textures_canonical_path.find_last_of("/\\"));
    textures_canonical_path += "/Textures";
}

std::string TextureManager::texture_path() const
{
    return textures_canonical_path;
}

Map TextureManager::generate_map(std::string json_path, std::vector <std::string> background_files)
{
    return Map(get_layers_from_json(json_path), background_files);
}

std::vector<Layer> TextureManager::get_layers_from_json(std::string path)
{
    nlohmann::json data = this->parse_to_json(path);
    std::vector <Layer> result;

    if (data.contains("layers") && data["layers"].is_array())
    {
        for (const auto& layer : data["layers"])
        {
            std::vector <Block> _layer;
            bool is_collidable = false;
            if (layer.contains("data") && layer["data"].is_array())
            {
                for (int i = 0; i < MAX_BLOCKS_VERTICAL; i++)
                {
                    for (int j = 0; j < MAX_BLOCKS_HORIZONTAL; j++)
                    {
                        uint16_t id = layer["data"][i + j].get<unsigned int>();
                        std::string name = layer["name"].get<std::string>();
                        if (id == 0) { continue; }
                        _layer.push_back(Block(id, this->get_file_from_id(id, get_type(name)), 32 * j, 32 * i));
                        name == COLLIDABLE_TILE ? is_collidable = true : is_collidable = false;
                    }
                }
                result.push_back(Layer(_layer, is_collidable));
            }
        }
    }
    return result;
}

nlohmann::json&& TextureManager::parse_to_json(std::string path)
{
    std::ifstream file(path);
    if (!file.is_open()) 
    {
        std::cerr << "Failed to open file." << std::endl;
        return 1;
    }

    nlohmann::json data;
    try {
        file >> data; // Parse JSON from the file into the json object
    }
    catch (nlohmann::json::parse_error& e) {
        std::cerr << "JSON parsing error: " << e.what() << std::endl;
        return 1;
    }
    return std::move(data);
}

std::string TextureManager::get_file_from_id(uint16_t id, Texture_Type type)
{
    std::string path = textures_canonical_path + "/Map_Textures";
    if (type == Texture_Type::TILE) { path += "/Tiles"; }
    else if (type == Texture_Type::OBJECT) { path += "/Objects"; }
    else if (type == Texture_Type::ANIMATED_OBJECT) { path += "/Animated objects"; }

    path += std::to_string(id);
    path += ".png";

    return path;
}

Texture_Type TextureManager::get_type(std::string name)
{
    if (name == COLLIDABLE_TILE or name == NON_COLLIDABLE_TILE) { return Texture_Type::TILE; }
    else if (name == NON_COLLIDABLE_OBJ) { return Texture_Type::OBJECT; }
    else { return Texture_Type::NONE; }
}
