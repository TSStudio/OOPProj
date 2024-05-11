#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <memory>

#include "Screen.h"

namespace sfSnake {
class Game {
public:
    Game();

    void run();

    void handleInput();
    void update(sf::Time delta);
    void render();

    static const int Width = 640;
    static const int Height = 480;

    static std::shared_ptr<Screen> ScreenPtr;
    sf::RenderWindow window_;
    static const sf::Time TimePerFrame;

private:
};
}  // namespace sfSnake

#endif