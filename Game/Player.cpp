//#include "Player.h"
//
//Player::Player(sf::String F, float X, float Y, float W, float H) {
//    dx = 0; dy = 0; speed = 0; dir = 0;
//    File = F;
//    w = W; h = H;
//    image.loadFromFile("C:/Users/Home/source/repos/Game/Textures/Character_Textures/Biker/" + File);
//    image.createMaskFromColor(sf::Color::White);
//    texture.loadFromImage(image);
//    sprite.setTexture(texture);
//    x = X; y = Y;
//    onGround = false;
//    isAlive = true;
//    sprite.setTextureRect(sf::IntRect(0, 0, w, h));
//    hitbox = sf::FloatRect(x, y, w, h);
//}
//
//void Player::move(float time, Map& map) {
//    bool keyPressed = false; // Flag to track if any movement keys are pressed
//
//    // Mirror the sprite if facing left
//    if (!isFacingRight) {
//        sprite.setScale(-1.0f, 1.0f); // Mirror horizontally
//    }
//    else {
//        sprite.setScale(1.0f, 1.0f); // Reset to normal
//    }
//
//    // Handle character movement with a static speed
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
//        dir = 1; speed = 0.15;
//        currentFrame += 0.005 * time;
//        isFacingRight = false; // Set facing direction to left
//        if (currentFrame > 6) currentFrame -= 6;
//        sprite.setTextureRect(sf::IntRect(48 * int(currentFrame), 33, 32, 32));
//        keyPressed = true; // A movement key is pressed
//    }
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
//        dir = 0; speed = 0.15;
//        currentFrame += 0.005 * time;
//        isFacingRight = true; // Set facing direction to right
//        if (currentFrame > 6) currentFrame -= 6;
//        sprite.setTextureRect(sf::IntRect(48 * int(currentFrame), 33, 32, 32));
//        keyPressed = true; // A movement key is pressed
//    }
//
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && onGround) {
//        std::cout << "UP IS PRESSED\n";
//        dir = 2; speed = 0.45f;
//        onGround = false;
//    }
//
//    if (!keyPressed) {
//        // No movement keys pressed, reset animation to IDLE frame
//        currentFrame = 0;
//        sprite.setTextureRect(sf::IntRect(0, 0, w, h));
//    }
//
//    update(time, map);
//}
//
//
//void Player::update(float time, Map& map) {
//    switch (dir)//реализуем поведение в зависимости от направления. (каждая цифра соответствует направлению)
//    {
//    case 0: dx = speed; break;//по иксу задаем положительную скорость, по игреку зануляем. получаем, что персонаж идет только вправо
//    case 1: dx = -speed; break;//по иксу задаем отрицательную скорость, по игреку зануляем. получается, что персонаж идет только влево
//    case 2: dy = -speed; break;//по иксу задаем нулевое значение, по игреку отрицательное. получается, что персонаж идет только вверх
//    default:
//        dx = 0; break;
//    }
//    std::cout << dx << " " << dy << "\n";
//    // Update player's position
//    y += dy * time;
//    x += dx * time;
//    check_collisions(map, dx, dy);
//
//    if (!onGround) {
//        //std::cout << "Applying gravity\n";
//        dy += 0.0015f * time; // Adjust this value for the desired gravity effect
//    }
//
//    speed = 0;
//    hitbox.left = x;
//    hitbox.top = y;
//    sprite.setPosition(x, y);
//}
//
//void Player::draw(sf::RenderWindow& window) {
//    window.draw(sprite); // Draw the player's sprite
//}
//
////void Player::check_collisions(Map& map, float dx, float dy) 
////{
////    if (x < 10 and y < 400) { x = 20; y = WINDOW_HEIGHT - 70; sprite.setPosition(x, y); return; }
////    if (x < 10) { x = 20; y = 370; sprite.setPosition(x, y); return; }
////    if (x > 6 * 32 and x < 9 * 32 and y < WINDOW_HEIGHT - 150) {
////        if (dx > 0) { this->dy = -speed; }
////        else if (dx < 0) { this->dy = speed; }
////        return;
////    }
////    //std::cout << x << " " << y << "\n" << x << " " << ceil(y + h + 0.5) << "\n\n\n";
////    for (int i = y / 32; i < (y + h * 0.456) / 32; i++) {
////        for (int j = x / 32; j < (x + w * 0.456) / 32; j++) {
////            std::cout << i << " " << j << "\n";
////            if (map.get_collision_grid()[i][j])
////            {
////                if (dy > 0) { y = i * 32 - (h * 0.456); this->dy = 0; onGround = true; }
////                if (dy < 0) { y = i * 32 + 32; this->dy = 0; }
////                if (dx > 0) { x = j * 32 - (w * 0.456); this->dx = 0; }
////                if (dx < 0) { x = j * 32 + 32; this->dx = 0; }
////            }
////        }
////    }
////}
////void Player::check_collisions(Map& map, float dx, float dy) 
////{
////    for (int i = y / 32; i < (y + h * 0.5) / 32; i++) {
////        for (int j = x / 32; j < (x + w * 0.5) / 32; j++) {
////            if (i < 0 and i >= map.get_collision_grid().size() and j < 0 and j >= map.get_collision_grid()[0].size()) {
////                if (map.get_collision_grid()[i][j] == 1)
////                {
////                    if (dy > 0) { y = i * 32 - (h * 0.5); this->dy = 0; onGround = true; }
////                    if (dy < 0) { y = i * 32 + 32; this->dy = 0; }
////                    if (dx > 0) { x = j * 32 - (w * 0.5); this->dx = 0; }
////                    if (dx < 0) { x = j * 32 + 32; this->dx = 0; }
////                }
////            }
////        }
////    }
////}
//void Player::set_position(float x, float y)
//{
//    this->x = x;
//    this->y = y;
//    this->hitbox.left = x;
//    this->hitbox.top = y;
//    this->sprite.setPosition(x, y);
//}
//
//void Player::check_collisions(Map& map, float dx, float dy) {
//    for (int i = y / 32; i < (y + h * 0.456) / 32; i++) {
//        for (int j = x / 32; j < (x + w * 0.456) / 32; j++) {
//            if (map.get_collision_grid()[i][j])
//            {
//                if (dy > 0) { y = i * 32 - (h * 0.462); this->dy = 0; onGround = true; }
//                if (dy < 0) { y = i * 32 + 32; this->dy = 0; }
//                if (dx > 0) { x = j * 32 - (w * 0.462); this->dx = 0; }
//                if (dx < 0) { x = j * 32 + 32; this->dx = 0; }
//            }
//        }
//    }
//}
