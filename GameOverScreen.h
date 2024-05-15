#ifndef GAME_OVER_SCREEN_H
#define GAME_OVER_SCREEN_H

#include <SFML/Graphics.hpp>

#include "Screen.h"
#include "Animation.h"

namespace sfSnake {
class GameOverScreen : public Screen {
public:
    GameOverScreen(std::size_t score);

    void handleInput(sf::RenderWindow& window) override;
    void update(sf::Time delta) override;
    void render(sf::RenderWindow& window) override;

private:
    const unsigned int lineHeight = 36;
    unsigned int base;

    unsigned int selectedItemIndex_;
    sf::Font font_;
    sf::Text texthsc_;
    sf::Text textsc_;
    sf::Text text_;
    sf::Text text2_;
    sf::Text text3_;
    sf::RectangleShape selection_;

    unsigned int animatedItemIndex_ = 0;
    Animation animation_;
    bool performingAnimation_ = false;

    unsigned score_;
};
}  // namespace sfSnake

#endif