#include "TextureManager.h"

TextureManager::TextureManager(char** argv)
{
    textures_canonical_path = std::filesystem::path(argv[0]).parent_path().string();
    textures_canonical_path = textures_canonical_path.substr(0, textures_canonical_path.find_last_of("/\\"));
    textures_canonical_path = textures_canonical_path.substr(0, textures_canonical_path.find_last_of("/\\"));
    textures_canonical_path += "/Textures";
}

std::string TextureManager::texture_path()
{
    return textures_canonical_path;
}

std::vector<std::vector<Block>> TextureManager::get_layers_from_json(std::string path)
{
    nlohmann::json data = this->parse_to_json(path);
    std::vector <std::vector <Block>> result;

    if (data.contains("layers") && data["layers"].is_array())
    {
        for (const auto& layer : data["layers"])
        {
            std::vector <Block> _layer;
            if (layer.contains("data") && layer["data"].is_array())
            {
                for (int i = 0; i < 20; i++)
                {
                    for (int j = 0; j < 32; j++)
                    {
                        if (layer["data"][i + j] == 0) { continue; }
                        _layer.push_back(Block(layer["data"][i + j], "", 32 * j, 32 * i));
                    }
                }
                result.push_back(_layer);
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

std::string TextureManager::get_file_from_id(uint16_t id, bool is_collidable)
{
    if (is_collidable)
    {

    }
}
