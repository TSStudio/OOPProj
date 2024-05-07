#ifndef SNAKE_NODE_H
#define SNAKE_NODE_H

#include <SFML/Graphics.hpp>

namespace sfSnake {
class NodePosition {
public:
    sf::Vector2f position;
    double degree;
};
class SnakeNode {
public:
    SnakeNode(sf::Vector2f position = sf::Vector2f(0, 0));

    void setPosition(sf::Vector2f position);
    void setPosition(float x, float y);

    void move(float xOffset, float yOffset);

    void render(sf::RenderWindow& window);

    sf::Vector2f getPosition() const;
    float getRadius() const;

    static const float Width;
    static const float Height;

private:
    sf::RectangleShape shape_;
    sf::CircleShape innerShape_;
    sf::Vector2f position_;
};
}  // namespace sfSnake

#endif