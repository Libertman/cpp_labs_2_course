#pragma once
#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>

class Ball {
private:
    sf::CircleShape shape;
    sf::Vector2f velocity;

public:
    Ball();
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);

    void bounceX();
    void bounceY();
    void speedUp(float factor);

    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;
    void reset();
};

#endif
