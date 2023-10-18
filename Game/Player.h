//#pragma once
//#include <SFML/Graphics.hpp>
//#include <nlohmann/json.hpp>
//#include "Block.h"
//#include "TextureManager.h"
//#include "Block.h"
//
//class Player {
//public:
//    friend class Engine;
//    Player(sf::String F, float X, float Y, float W, float H);
//    void update(float time, Map& map);
//    void move(float time, Map& map);
//    void draw(sf::RenderWindow& window); // Function to draw the player sprite
//    void check_collisions(Map& map, float dx, float dy);
//    void set_position(float x, float y);
//private:
//    float currentFrame = 0;
//    static constexpr float GRAVITY = 0.0015f;
//    static constexpr float JUMP_STRENGTH = -10.0f;
//    bool isJumping = false;
//    float jumpSpeed;
//    float jumpHeight;
//    bool isFacingRight = true;
//    float x, y, w, h, dx, dy, speed;
//    bool onGround, isAlive;
//    int dir = 0;
//    sf::String File;
//    sf::Image image;
//    sf::Texture texture;
//    sf::Sprite sprite;
//    sf::FloatRect hitbox;
//};
