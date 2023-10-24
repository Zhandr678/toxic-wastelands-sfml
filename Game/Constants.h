#pragma once
#include <string>

#define NULL_FILE "NULL"

enum class Texture_Type
{
    NONE, COLLIDABLE_TILE, NON_COLLIDABLE_TILE, OBJECT, ANIMATED_OBJECT
};

constexpr size_t TIME_SCALING          = 800;
constexpr size_t TILE_SIZE             = 32;
constexpr size_t MAX_BLOCKS_HORIZONTAL = 32;
constexpr size_t MAX_BLOCKS_VERTICAL   = 20;
constexpr size_t WINDOW_LENGTH         = 1000;
constexpr size_t WINDOW_HEIGHT         = 600;

constexpr float DEFAULT_SPEED   = 0.15f;
constexpr float DEFAULT_GRAVITY = 0.0015f;
constexpr float DEFAULT_MAX_HP  = 100.0f;

constexpr float UNHARMFUL_Y_SPEED      = 0.8f;
constexpr float DAMAGE_RATE_PER_SPEED  = 30.0f;
constexpr float DAMAGE_POWER_PER_SPEED = 2.0f;

const std::string NON_COLLIDABLE_TILE = "notCollidable-tile";
const std::string NON_COLLIDABLE_OBJ = "notCollidable-obj";
const std::string COLLIDABLE_TILE = "collidable-tile";
const std::string BACKGROUND = "C:/Users/Home/source/repos/Game/Textures/Map_Textures/Background/background.png";