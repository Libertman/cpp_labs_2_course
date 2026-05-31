#include "Block.h"

Block::Block(float x, float y, float width, BlockType type) : type(type), destroyed(false) {
    shape.setPosition(x, y);
    shape.setSize(sf::Vector2f(width, BLOCK_HEIGHT));

    switch (type) {
    case BlockType::Normal:
        shape.setFillColor(sf::Color::Red);
        break;
    case BlockType::Indestructible:
        shape.setFillColor(sf::Color(128, 128, 128));
        break;
    case BlockType::SpeedUp:
        shape.setFillColor(sf::Color::Magenta);
        break;
    case BlockType::BonusHolder:
        shape.setFillColor(sf::Color::Yellow);
        break;
    }
}

bool Block::hit() {
    if (type == BlockType::Indestructible) {
        return false;
    }
    destroyed = true;
    return true;
}

bool Block::isDestroyed() const { return destroyed; }
BlockType Block::getType() const { return type; }
sf::FloatRect Block::getBounds() const { return shape.getGlobalBounds(); }

void Block::draw(sf::RenderWindow& window) {
    if (!destroyed) {
        window.draw(shape);
    }
}
