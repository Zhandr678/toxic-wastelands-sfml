#pragma once
#include <string>

#define NULL_FILE "NULL"

enum class Texture_Type
{
    NONE, COLLIDABLE_TILE, NON_COLLIDABLE_TILE, OBJECT, ANIMATED_OBJECT
};

enum class Entity_State
{
    IDLE, MOVING_RIGHT, MOVING_LEFT, JUMP, ATTACK, DIE
};

enum class HPBar_Display
{
    FIXED, ABSOLUTE, BOUND
};

enum class EntityGroup
{
    PC, NPC
};

enum class Game_State
{
    MENU, GAME, DEATH, FINISH
};

constexpr size_t TIME_SCALING = 800;
constexpr size_t TILE_SIZE = 32;
constexpr size_t MAX_BLOCKS_HORIZONTAL = 60;
constexpr size_t MAX_BLOCKS_VERTICAL = 15;
constexpr float WINDOW_LENGTH = 1000.0f;
constexpr float WINDOW_HEIGHT = 600.0f;

constexpr float DEFAULT_SPEED = 0.15f;
constexpr float DEFAULT_GRAVITY = 0.0015f;
constexpr float DEFAULT_MAX_HP = 100.0f;
constexpr float DEFAULT_DAMAGE = 15.0f;

constexpr float UNHARMFUL_Y_SPEED = 0.8f;
constexpr float DAMAGE_RATE_PER_SPEED = 35.5872f;
constexpr float DAMAGE_POWER_PER_SPEED = 4.5357f;

const std::string NON_COLLIDABLE_TILE = "notCollidable-tile";
const std::string NON_COLLIDABLE_OBJ = "notCollidable-obj";
const std::string COLLIDABLE_TILE = "collidable-tile";
const std::string BACKGROUND = "C:/Users/Home/source/repos/Game/Textures/Map_Textures/Background/map";