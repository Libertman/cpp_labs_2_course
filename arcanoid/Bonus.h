#pragma once
#ifndef BONUS_H
#define BONUS_H

#include <SFML/Graphics.hpp>
#include "Config.h"

class Bonus {
private:
    sf::CircleShape shape;
    BonusType type;
    bool active;
    float speed;

public:
    Bonus(float x, float y, BonusType type);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);

    bool isActive() const;
    void deactivate();
    sf::FloatRect getBounds() const;
};

#endif
