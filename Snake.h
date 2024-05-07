#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>
#include <deque>

#include "SnakeNode.h"
#include "Fruit.h"

namespace sfSnake {
class Direction {
public:
    double degree;
    double get_dx();
    double get_dy();
    Direction() : degree(0) {}
};

class Snake {
public:
    Snake(bool player = true);

    void handleInput();
    void update(sf::Time delta);
    void render(sf::RenderWindow& window);

    void checkFruitCollisions(std::vector<Fruit>& fruits);
    void checkOtherSnakeCollisions(Snake& otherSnake);

    bool hit() const;

    unsigned getSize() const;
    void doAIMovement(sf::Vector2f target);

    void initNodes(float x, float y);
    void initNodes();
    std::vector<SnakeNode> nodes_;

private:
    bool player;
    void move();
    void grow();
    void melt();
    void checkEdgeCollisions();

    bool hit_;

    sf::Vector2f position_;
    Direction direction_;

    sf::SoundBuffer pickupBuffer_;
    sf::Sound pickupSound_;

    sf::SoundBuffer dieBuffer_;
    sf::Sound dieSound_;

    std::deque<NodePosition> nodePositions_;

    static const int InitialSize;
};
}  // namespace sfSnake

#endif