#include <SFML/Graphics.hpp>

#include <random>
#include <memory>

#include "GameScreen.h"
#include "GameOverScreen.h"
#include "Background.h"
#include "Game.h"
#include "Random.h"
#include "Benchmark.h"

using namespace sfSnake;

extern Benchmark global_benchmark;

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

    bgMusic_.openFromFile("Music/bg_music.wav");
    bgMusic_.setLoop(true);
    bgMusic_.play();
    powerMusic_.openFromFile("Music/power_music.wav");

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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
        global_benchmark = Benchmark();
    }
    snake_.handleInput();
}

void GameScreen::update(sf::Time delta) {
    global_benchmark.in_section("GameScreen::update");

    global_benchmark.in_section("GameScreen::update::generateFruit");
    if (fruit_.size() < 8) {
        int x = Random::randomInt(0, 10);
        if (x < 1) {
            generateFruit();
        }
    }
    global_benchmark.out_section();

    global_benchmark.in_section("GameScreen::update::snake_.update");
    snake_.update(delta);
    global_benchmark.out_section();

    global_benchmark.in_section("GameScreen::update::snake_.checkFruitCollisions");
    snake_.checkFruitCollisions(fruit_);
    global_benchmark.out_section();

    if (snake_.hit()) {
        Game::ScreenPtr = std::make_shared<GameOverScreen>(snake_.getSize());
        return;
    }

    global_benchmark.in_section("GameScreen::update::AIsnake_.update");
    if (AIsnakeAlive_) {
        global_benchmark.in_section("GameScreen::update::AIsnake_.doAIMovement");
        if (fruit_.size()) {
            AIsnakes_[0].doAIMovement(fruit_[0].getPosition());
        }
        global_benchmark.out_section();
        global_benchmark.in_section("GameScreen::update::AIsnake_.other");
        AIsnakes_[0].update(delta);
        AIsnakes_[0].checkFruitCollisions(fruit_);
        snake_.checkOtherSnakeCollisions(AIsnakes_[0]);

        AIsnakes_[0].checkOtherSnakeCollisions(snake_);
        if (AIsnakes_[0].hit()) {
            AIsnakeAlive_ = false;
            for (auto& node : AIsnakes_[0].nodes_) {
                if (Random::randomInt(0, 1)) continue;
                fruit_.push_back(Fruit(node.getPosition(), 1));
            }
            if (powerMusic_.getStatus() != sf::Music::Playing) {
                bgMusic_.pause();
                powerMusic_.setPlayingOffset(sf::seconds(0));
                powerMusic_.play();
            }
        }
        global_benchmark.out_section();
    }
    global_benchmark.out_section();

    if ((powerMusic_.getStatus() != sf::Music::Playing)) {
        if (bgMusic_.getStatus() != sf::Music::Playing)
            bgMusic_.play();
    }

    global_benchmark.in_section("GameScreen::update::generate_new_AIsnake");
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
    global_benchmark.out_section();
    global_benchmark.out_section();
    background_.updateScore(snake_.score_);
}

void GameScreen::render(sf::RenderWindow& window) {
    global_benchmark.in_section("GameScreen::render");
    global_benchmark.in_section("GameScreen::render::background_.render");
    background_.render(window);
    global_benchmark.out_section();

    global_benchmark.in_section("GameScreen::render::snake_.render");
    snake_.render(window);
    global_benchmark.out_section();
    global_benchmark.in_section("GameScreen::render::AIsnake_.render");
    if (AIsnakeAlive_)
        AIsnakes_[0].render(window);
    global_benchmark.out_section();
    global_benchmark.in_section("GameScreen::render::fruit_.render");

    for (auto fruit : fruit_)
        fruit.render(window);
    global_benchmark.out_section();

    global_benchmark.out_section();
    global_benchmark.print_result();
}

void GameScreen::generateFruit() {
    static std::default_random_engine engine;
    engine.seed(time(NULL));
    static std::uniform_int_distribution<int> xDistribution(0, Game::Width - SnakeNode::Width);
    static std::uniform_int_distribution<int> yDistribution(0, Game::Height - SnakeNode::Height);

    fruit_.push_back(Fruit(Random::randomPosition(0, Game::Width - SnakeNode::Width, 0, Game::Height - SnakeNode::Height), Random::randomInt(0, 3)));
}
