#include "Bonus.h"


Bonus::Bonus(float x, float y, BonusType type) : type(type), active(true), speed(200.0f) {
    shape.setRadius(8.0f);
    shape.setFillColor(sf::Color::Green);
    shape.setOrigin(8.0f, 8.0f);
    shape.setPosition(x, y);
}

void Bonus::update(float deltaTime) {
    shape.move(0, speed * deltaTime);
    if (shape.getPosition().y > WINDOW_HEIGHT) {
        active = false;
    }
}

void Bonus::draw(sf::RenderWindow& window) {
    if (active) window.draw(shape);
}

bool Bonus::isActive() const { return active; }
void Bonus::deactivate() { active = false; }
sf::FloatRect Bonus::getBounds() const { return shape.getGlobalBounds(); }
