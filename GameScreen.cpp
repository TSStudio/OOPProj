#include <SFML/Graphics.hpp>

#include <random>
#include <memory>

#include "GameScreen.h"
#include "GameOverScreen.h"
#include "Background.h"
#include "Game.h"
#include "Random.h"

using namespace sfSnake;

GameScreen::GameScreen() : snake_(), AIsnakes_(), AIsnakeAlive_(true) {
    snake_.initNodes();
    AIsnakes_.push_back(Snake(false));
    float AI_x = Random::randomFloat(Game::Width * 0.2, Game::Width * 0.8);
    float AI_y = Random::randomFloat(Game::Height * 0.2, Game::Height * 0.8);
    while (abs(AI_x - snake_.nodes_[0].getPosition().x) + abs(AI_y - snake_.nodes_[0].getPosition().y) < 5 * SnakeNode::Width) {
        AI_x = Random::randomFloat(Game::Width * 0.2, Game::Width * 0.8);
        AI_y = Random::randomFloat(Game::Height * 0.2, Game::Height * 0.8);
    }
    AIsnakes_[0].initNodes(AI_x, AI_y);

    background_ = Background();
}

void GameScreen::handleInput(sf::RenderWindow& window) {
    static bool key_Q_state_last = false;
    static bool key_W_state_last = false;
    static bool key_E_state_last = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        if (!key_Q_state_last) {
            background_.switch_bg_color();
        }
        key_Q_state_last = true;
    } else {
        key_Q_state_last = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        if (!key_W_state_last) {
            background_.switch_grid_color();
        }
        key_W_state_last = true;
    } else {
        key_W_state_last = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
        if (!key_E_state_last) {
            background_.switch_grid();
        }
        key_E_state_last = true;
    } else {
        key_E_state_last = false;
    }
    snake_.handleInput();
}

void GameScreen::update(sf::Time delta) {
    if (fruit_.size() < 8) {
        int x = Random::randomInt(0, 10);
        if (x < 1) {
            generateFruit();
        }
    }

    snake_.update(delta);
    snake_.checkFruitCollisions(fruit_);

    if (snake_.hit()) {
        Game::ScreenPtr = std::make_shared<GameOverScreen>(snake_.getSize());
        return;
    }

    if (AIsnakeAlive_) {
        if (fruit_.size()) {
            AIsnakes_[0].doAIMovement(fruit_[0].getPosition());
        }
        AIsnakes_[0].update(delta);
        AIsnakes_[0].checkFruitCollisions(fruit_);
        snake_.checkOtherSnakeCollisions(AIsnakes_[0]);
        AIsnakes_[0].checkOtherSnakeCollisions(snake_);
        if (AIsnakes_[0].hit()) {
            AIsnakeAlive_ = false;
            //todo: drop fruit
            for (auto& node : AIsnakes_[0].nodes_) {
                if (Random::randomInt(0, 1)) continue;
                fruit_.push_back(Fruit(node.getPosition(), 1));
            }
        }
    }
    if (!AIsnakeAlive_) {
        AIsnakes_.erase(AIsnakes_.begin());
        AIsnakes_.push_back(Snake(false));
        float AI_x = Random::randomFloat(Game::Width * 0.2, Game::Width * 0.8);
        float AI_y = Random::randomFloat(Game::Height * 0.2, Game::Height * 0.8);
        sf::Vector2f player_pos = snake_.nodes_[0].getPosition();
        while (abs(AI_x - player_pos.x) + abs(AI_y - player_pos.y) < 3 * SnakeNode::Width) {
            AI_x = Random::randomFloat(Game::Width * 0.2, Game::Width * 0.8);
            AI_y = Random::randomFloat(Game::Height * 0.2, Game::Height * 0.8);
        }
        AIsnakes_[0].initNodes(AI_x, AI_y);
        AIsnakeAlive_ = true;
    }
    background_.updateScore(snake_.score_);
}

void GameScreen::render(sf::RenderWindow& window) {
    background_.render(window);
    snake_.render(window);
    if (AIsnakeAlive_)
        AIsnakes_[0].render(window);

    for (auto fruit : fruit_)
        fruit.render(window);
}

void GameScreen::generateFruit() {
    static std::default_random_engine engine;
    engine.seed(time(NULL));
    static std::uniform_int_distribution<int> xDistribution(0, Game::Width - SnakeNode::Width);
    static std::uniform_int_distribution<int> yDistribution(0, Game::Height - SnakeNode::Height);

    fruit_.push_back(Fruit(Random::randomPosition(0, Game::Width - SnakeNode::Width, 0, Game::Height - SnakeNode::Height), Random::randomInt(0, 3)));
}
