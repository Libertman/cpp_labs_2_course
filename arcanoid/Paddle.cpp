#include "Paddle.h"
#include "Config.h"


Paddle::Paddle() : speed(PADDLE_SPEED), width(PADDLE_START_WIDTH) {
    shape.setSize(sf::Vector2f(width, PADDLE_HEIGHT));
    shape.setFillColor(sf::Color::White);
    resetPosition();
}

void Paddle::resetPosition() {
    shape.setPosition((WINDOW_WIDTH - width) / 2.0f, WINDOW_HEIGHT - 50.0f);
}

void Paddle::shrink() {
    width = std::max(60.0f, width - 20.0f);
    shape.setSize(sf::Vector2f(width, PADDLE_HEIGHT));
}

void Paddle::update(float deltaTime) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        shape.move(-speed * deltaTime, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        shape.move(speed * deltaTime, 0);
    }

    sf::Vector2f pos = shape.getPosition();
    if (pos.x < 0) shape.setPosition(0, pos.y);
    if (pos.x + width > WINDOW_WIDTH) shape.setPosition(WINDOW_WIDTH - width, pos.y);
}

void Paddle::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

sf::FloatRect Paddle::getBounds() const {
    return shape.getGlobalBounds();
}
