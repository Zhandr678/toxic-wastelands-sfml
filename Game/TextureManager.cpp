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

Map TextureManager::generate_map(std::string json_path, std::string background_file)
{
    nlohmann::json data = this->parse_to_json(json_path);
    std::vector <Layer> result;

    if (data.contains("layers") and data["layers"].is_array())
    {
        nlohmann::json layers = data["layers"];
        
        for (const auto& layer : layers)
        {
            std::string name = layer["name"];
            Texture_Type type = this->get_type(name);
            if (layer.contains("data") and layer["data"].is_array())
            {
                std::vector <std::vector <Block>> full_layer;
                std::vector <std::vector <bool>> full_hitbox_grid;
                for (int i = 0; i < MAX_BLOCKS_VERTICAL; i++)
                {
                    std::vector <Block> _layer;
                    std::vector <bool> _hitbox_grid;
                    for (int j = 0; j < MAX_BLOCKS_HORIZONTAL; j++)
                    {
                        uint16_t id = layer["data"][i * MAX_BLOCKS_HORIZONTAL + j];
                        
                        if (id == 0) 
                        { 
                            _layer.push_back(__NULL_BLOCK__()); 
                            _hitbox_grid.push_back(false);
                        }
                        else 
                        {
                            _layer.push_back(Block(id, this->get_file_from_id(id, type), static_cast<float>(32 * j), static_cast<float>(32 * i)));
                            _hitbox_grid.push_back(true);
                        }
                    }
                    full_layer.push_back(_layer);
                    full_hitbox_grid.push_back(_hitbox_grid);
                }
                result.push_back(Layer(name, full_layer, full_hitbox_grid, type));
            }
        }
    }
    return Map(result, background_file);
}

nlohmann::json TextureManager::parse_to_json(std::string path)
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
    return data;
}

std::string TextureManager::get_file_from_id(uint16_t id, Texture_Type type)
{
    std::string path = textures_canonical_path + "/Map_Textures";
    if (type == Texture_Type::COLLIDABLE_TILE or type == Texture_Type::NON_COLLIDABLE_TILE) { path += "/Tiles"; }
    else if (type == Texture_Type::OBJECT) { path += "/Objects"; }
    else if (type == Texture_Type::ANIMATED_OBJECT) { path += "/Animated objects"; }

    path += "/" + std::to_string(id);
    path += ".png";

    return path;
}

Texture_Type TextureManager::get_type(std::string name)
{
    if (name == COLLIDABLE_TILE) { return Texture_Type::COLLIDABLE_TILE; }
    else if (name == NON_COLLIDABLE_TILE) { return Texture_Type::NON_COLLIDABLE_TILE; }
    else if (name == NON_COLLIDABLE_OBJ) { return Texture_Type::OBJECT; }
    else { return Texture_Type::NONE; }
}
