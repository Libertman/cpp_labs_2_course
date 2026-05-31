#pragma once
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Paddle.h"
#include "Ball.h"
#include "Block.h"
#include "Bonus.h"

class Game {
private:
    sf::RenderWindow window;
    Paddle paddle;
    Ball ball;
    std::vector<Block> blocks;
    std::vector<Bonus> bonuses;

    int score;
    int lives;
    bool safetyFloorActive;
    sf::RectangleShape safetyFloorVisual;

    void initBlocks();
    void processEvents();
    void update(float deltaTime);
    void render();
    void checkCollisions();
    void updateTitle();

public:
    Game();
    void run();
};

#endif
