#include "Ball.h"
#include "Config.h"
#include <cmath>

Ball::Ball() {
    shape.setRadius(BALL_RADIUS);
    shape.setFillColor(sf::Color::Cyan);
    shape.setOrigin(BALL_RADIUS, BALL_RADIUS);
    reset();
}

void Ball::reset() {
    shape.setPosition(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f + 50.0f);
    velocity = sf::Vector2f(BALL_START_SPEED, -BALL_START_SPEED);
}

void Ball::update(float deltaTime) {
    shape.move(velocity * deltaTime);

    if (shape.getPosition().x - BALL_RADIUS < 0) {
        shape.setPosition(BALL_RADIUS, shape.getPosition().y);
        bounceX();
    }
    if (shape.getPosition().x + BALL_RADIUS > WINDOW_WIDTH) {
        shape.setPosition(WINDOW_WIDTH - BALL_RADIUS, shape.getPosition().y);
        bounceX();
    }

    if (shape.getPosition().y - BALL_RADIUS < 0) {
        shape.setPosition(shape.getPosition().x, BALL_RADIUS);
        bounceY();
    }
}

void Ball::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

void Ball::bounceX() { velocity.x = -velocity.x; }
void Ball::bounceY() { velocity.y = -velocity.y; }

void Ball::speedUp(float factor) {
    velocity *= factor;
}

sf::FloatRect Ball::getBounds() const {
    return shape.getGlobalBounds();
}

sf::Vector2f Ball::getPosition() const {
    return shape.getPosition();
}
