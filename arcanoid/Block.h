#pragma once
#ifndef BLOCK_H
#define BLOCK_H

#include <SFML/Graphics.hpp>
#include "Config.h"

class Block {
private:
    sf::RectangleShape shape;
    BlockType type;
    bool destroyed;

public:
    Block(float x, float y, float width, BlockType type);
    void draw(sf::RenderWindow& window);
    bool hit();

    bool isDestroyed() const;
    BlockType getType() const;
    sf::FloatRect getBounds() const;
};

#endif
