#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include <SFML/Graphics.hpp>

#include "Screen.h"
#include "Snake.h"
#include "Fruit.h"

namespace sfSnake {
const std::vector<sf::Color> avail_bg_color = {sf::Color(240, 240, 240), sf::Color(15, 15, 15), sf::Color(69, 21, 14)};
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
    unsigned bg_color_idx = 0;
    unsigned grid_color_idx = 1;
    sf::RectangleShape background_;
    void switch_bg_color();
};
}  // namespace sfSnake

#endif