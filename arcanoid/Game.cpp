#include "Game.h"
#include "Config.h"
#include <string>
#include <cstdlib>
#include <ctime>

Game::Game() :
    window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Arkanoid"),
    score(0), lives(3), safetyFloorActive(false)
{
    window.setFramerateLimit(60);
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    initBlocks();

    safetyFloorVisual.setSize(sf::Vector2f(WINDOW_WIDTH, 10.0f));
    safetyFloorVisual.setFillColor(sf::Color::Blue);
    safetyFloorVisual.setPosition(0, WINDOW_HEIGHT - 10.0f);
}

void Game::initBlocks() {
    float blockWidth = (WINDOW_WIDTH - (BLOCK_COLS + 1) * BLOCK_PADDING) / BLOCK_COLS;

    for (int r = 0; r < BLOCK_ROWS; ++r) {
        for (int c = 0; c < BLOCK_COLS; ++c) {
            float x = BLOCK_PADDING + c * (blockWidth + BLOCK_PADDING);
            float y = BLOCK_PADDING + r * (BLOCK_HEIGHT + BLOCK_PADDING) + 50.0f;

            int randType = std::rand() % 10;
            BlockType type = BlockType::Normal;
            if (randType == 0 || randType == 1) type = BlockType::Indestructible; 
            else if (randType == 2) type = BlockType::SpeedUp;
            else if (randType == 3) type = BlockType::BonusHolder;

            blocks.emplace_back(x, y, blockWidth, type);
        }
    }
}

void Game::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        processEvents();
        update(deltaTime);
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Game::update(float deltaTime) {
    paddle.update(deltaTime);
    ball.update(deltaTime);

    for (auto& bonus : bonuses) {
        bonus.update(deltaTime);
    }

    checkCollisions();
    updateTitle();
}

void Game::checkCollisions() {
    sf::FloatRect ballBounds = ball.getBounds();

    if (ballBounds.intersects(paddle.getBounds())) {
        ball.bounceY();
    }

    for (auto& block : blocks) {
        if (!block.isDestroyed() && ballBounds.intersects(block.getBounds())) {
            ball.bounceY();

            if (block.hit()) {
                score += 10;

                if (block.getType() == BlockType::SpeedUp) {
                    ball.speedUp(1.2f);
                }

                if (block.getType() == BlockType::BonusHolder) {
                    bonuses.emplace_back(block.getBounds().left + block.getBounds().width / 2, block.getBounds().top, BonusType::SafetyFloor);
                }
            }
            break;
        }
    }

    for (auto& bonus : bonuses) {
        if (bonus.isActive() && bonus.getBounds().intersects(paddle.getBounds())) {
            bonus.deactivate();
            safetyFloorActive = true;
        }
    }

    if (ball.getPosition().y + BALL_RADIUS > WINDOW_HEIGHT) {
        if (safetyFloorActive) {
            ball.bounceY();
            safetyFloorActive = false;
        }
        else {
            score = std::max(0, score - 50);
            lives--;
            paddle.shrink();
            ball.reset();
            paddle.resetPosition();

            if (lives <= 0) {
                lives = 3;
                score = 0;
                blocks.clear();
                bonuses.clear();
                initBlocks();
            }
        }
    }
}

void Game::updateTitle() {
    std::string title = "Arkanoid | Score: " + std::to_string(score) +
        " | Lives: " + std::to_string(lives) +
        (safetyFloorActive ? " | [SHIELD ACTIVE]" : "");
    window.setTitle(title);
}

void Game::render() {
    window.clear(sf::Color::Black);

    paddle.draw(window);
    ball.draw(window);

    for (auto& block : blocks) {
        block.draw(window);
    }

    for (auto& bonus : bonuses) {
        bonus.draw(window);
    }

    if (safetyFloorActive) {
        window.draw(safetyFloorVisual);
    }

    window.display();
}
