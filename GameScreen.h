#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include <SFML/Graphics.hpp>

#include "Screen.h"
#include "Snake.h"
#include "Fruit.h"
#include "Background.h"

namespace sfSnake {
class GameScreen : public Screen {
public:
    GameScreen();

    void handleInput(sf::RenderWindow& window) override;
    void update(sf::Time delta) override;
    void render(sf::RenderWindow& window) override;

    void generateFruit();

private:
    Snake snake_;
    std::vector<Snake> AIsnakes_;
    bool AIsnakeAlive_;
    std::vector<Fruit> fruit_;
    Background background_;
    sf::Music bgMusic_;
    sf::Music powerMusic_;
};
}  // namespace sfSnake

#endif