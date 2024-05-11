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
    SnakeNode(sf::Vector2f position = sf::Vector2f(0, 0), bool head = false, sf::Color color = sf::Color::Green);
    SnakeNode(const SnakeNode& old);

    void setPosition(sf::Vector2f position);
    void setPosition(float x, float y);
    void setPosition(NodePosition nodePosition);

    void move(float xOffset, float yOffset);

    void render(sf::RenderWindow& window);

    sf::Vector2f getPosition() const;
    float getRadius() const;

    static const float Width;
    static const float Height;
    bool head_ = false;
    sf::Texture texture_;

private:
    sf::RectangleShape shape_;
    sf::CircleShape innerShape_;
    sf::Vector2f position_;
    sf::Color color_;
    double degree_;

    sf::Sprite sprite_;
};
}  // namespace sfSnake

#endif