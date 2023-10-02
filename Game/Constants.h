#pragma once
#include <string>
#include <filesystem>
#include <vector>

#define NULL_FILE "NULL"

enum class Texture_Type
{
    NONE, TILE, OBJECT, ANIMATED_OBJECT
};

constexpr size_t TIME_SCALING = 800;
constexpr size_t TILE_SIZE = 32;
constexpr size_t MAX_BLOCKS_HORIZONTAL = 32;
constexpr size_t MAX_BLOCKS_VERTICAL = 20;
constexpr size_t WINDOW_LENGTH = 1080;
constexpr size_t WINDOW_HEIGHT = 640;

const std::string NON_COLLIDABLE_TILE = "notCollidable-tile";
const std::string NON_COLLIDABLE_OBJ = "notCollidable-obj";
const std::string COLLIDABLE_TILE = "collidable-tile";