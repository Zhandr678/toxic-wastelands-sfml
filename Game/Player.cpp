#include "Player.h"

Player::Player(sf::String F, float X, float Y, float W, float H) {
    dx = 0; dy = 0; speed = 0; dir = 0;
    File = F;
    w = W; h = H;
    image.loadFromFile("C:/Users/Home/source/repos/Game/Textures/Character_Textures/Biker/" + File);
    image.createMaskFromColor(sf::Color::White);
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    x = X; y = Y;
    onGround = false;
    isAlive = true;
    sprite.setTextureRect(sf::IntRect(0, 0, w, h));
    hitbox = sf::FloatRect(x, y, w, h);
}

void Player::move(float time, Map& map) {
    bool keyPressed = false; // Flag to track if any movement keys are pressed

    // Mirror the sprite if facing left
    if (!isFacingRight) {
        sprite.setScale(-1.0f, 1.0f); // Mirror horizontally
    }
    else {
        sprite.setScale(1.0f, 1.0f); // Reset to normal
    }

    // Handle character movement with a static speed
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        dir = 1; speed = 0.1;
        currentFrame += 0.005 * time;
        isFacingRight = false; // Set facing direction to left
        if (currentFrame > 6) currentFrame -= 6;
        sprite.setTextureRect(sf::IntRect(48 * int(currentFrame), 48, 48, 48));
        keyPressed = true; // A movement key is pressed
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        dir = 0; speed = 0.1;
        currentFrame += 0.005 * time;
        isFacingRight = true; // Set facing direction to right
        if (currentFrame > 6) currentFrame -= 6;
        sprite.setTextureRect(sf::IntRect(48 * int(currentFrame), 48, 32, 48));
        keyPressed = true; // A movement key is pressed
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !isJumping) {
        // Start the jump
        isJumping = true;
        jumpSpeed = -0.2;  // Adjust this value for the desired jump height and speed
        jumpHeight = 100.0; // Adjust this value for the desired jump height
    }

    if (isJumping) {
        // Handle the jump
        dy = jumpSpeed;
        jumpSpeed += 0.005; // Adjust this value to control the gravity effect on the jump

        // Check if the jump has reached its peak
        if (jumpSpeed >= 0) {
            isJumping = false;
        }
    }

    if (!keyPressed) {
        // No movement keys pressed, reset animation to IDLE frame
        currentFrame = 0;
        sprite.setTextureRect(sf::IntRect(0, 0, w, h));
    }

    update(time, map);
}


void Player::update(float time, Map& map) {
    switch (dir)//реализуем поведение в зависимости от направления. (каждая цифра соответствует направлению)
    {
    case 0: dx = speed; dy = 0; break;//по иксу задаем положительную скорость, по игреку зануляем. получаем, что персонаж идет только вправо
    case 1: dx = -speed; dy = 0; break;//по иксу задаем отрицательную скорость, по игреку зануляем. получается, что персонаж идет только влево
    case 2: dx = 0; dy = speed; break;//по иксу задаем нулевое значение, по игреку положительное. получается, что персонаж идет только вниз
    case 3: dx = 0; dy = -speed; break;//по иксу задаем нулевое значение, по игреку отрицательное. получается, что персонаж идет только вверх
    }

    // Apply gravity
    //if (!isJumping) {
    //    dy += 0.0001 * time; // Adjust this value for the desired gravity effect
    //}

    // Update player's position
    x += dx * time;
    check_collisions(map, dx, 0);
    y += dy * time;
    check_collisions(map, 0, dy);

    speed = 0;
    hitbox.left = x;
    hitbox.top = y;
    sprite.setPosition(x, y);
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite); // Draw the player's sprite
}

void Player::check_collisions(Map& map, float dx, float dy)
{
    //std::cout << x << " " << y << "\n" << x << " " << ceil(y + h + 0.5) << "\n\n\n";
    int tx = x, ty = y;
    if (dy > 0 and map.get_block_at(x, ceil(y + h + 0.5)))
    {
        y = ty;
        this->dy = 0;
    }
    else if (dy < 0 and map.get_block_at(x, floor(y - 0.5)))
    {
        y = ty;
        this->dy = 0;
    }
    else if (dx > 0 and map.get_block_at(ceil(x + w + 0.5), y))
    {
        x = tx;
        this->dx = 0;
    }
    else if (dx < 0 and map.get_block_at(floor(x - 0.5), y))
    {
        x = tx;
        this->dx = 0;
    }
}

float Player::getX() const {
    return x;
}